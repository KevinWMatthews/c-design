/**
 * @file api_race_gnuc_sync.c
 *
 * TODO use __atomic builtins instead!
 * Fixing an API race using GNU C's __sync built-ins.
 *
 * TODO can we use __sync_lock_test_and_set() with __sync_lock_release()?
 * https://gcc.gnu.org/onlinedocs/gcc-4.1.1/gcc/Atomic-Builtins.html
 * TODO find a release elsewhere else
 * https://github.com/openbsd/src/blob/87afc19ed9256ae3cb7c5266911abf02218c2a35/lib/libc/thread/rthread_mutex.c
 *
 * This is based on OpenBSD's mutex implementation.
 * TODO run this with multiple threads and the thread sanitizer!!
 *
 * From the BSD implementation of pthread,
 * openbsd/src/lib/libc/thread/rthread.c,
 * @code
function _rthread_mutex_trylock() {
    // ...
    if (atomic_cas_uint(&mutex->lock, UNLOCKED, LOCKED) == UNLOCKED) {
        membar_enter_after_atomic();
        mutex->owner = self;
        return (0);
    }
}
 * @endcode
 *
 * On x86 with gcc and Linux, this appears to reduce to:
 * @code
function _rthread_mutex_trylock() {
    // ...
    if (__sync_val_compare_and_swap(&mutex->lock, UNLOCKED, LOCKED) == UNLOCKED) {
        __sync_synchronize();
        mutex->owner = self;
        return (0);
    }
}
 * @endcode
 *
 * Unlocking the mutex is similar:
 * @code
function pthread_mutex_unlock() {
 	membar_exit_before_atomic();
	if (atomic_dec_int_nv(&mutex->lock) != UNLOCKED) {
		mutex->lock = UNLOCKED;
        _wake(&mutex->lock, 1);
	}
    return 0;
}
 * @endcode
 *
 * On x86 with gcc and Linux, this appears to reduce to:
 * @code
function pthread_mutex_unlock() {
 	__sync_synchronize();
	if (__sync_sub_and_fetch(...) != UNLOCKED) {
		mutex->lock = UNLOCKED;
        _wake(&mutex->lock, 1);
	}
    return 0;
}
 * @endcode
 */

#ifndef __GNUC__

#include <stdio.h>

int main(void)
{
    printf("Example requires a GNU C compiler\n");
    return -1;
}

#else

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// TODO do these need a "volatile" flag?
static bool event_flag = true;
static int event_state;

int main(void)
{
    printf("Starting...\n");
    __useconds_t loop_delay_ms = 100;

    while (1)
    {
        // Don't forget to exit!

        // Using gcc builtins for x86
        if (__sync_bool_compare_and_swap(&event_flag, true, false))
        {
            // TODO look into this!
            __sync_synchronize();
            int local_state = event_state;
            __sync_synchronize();

            printf("Event state: '%d'\n", local_state);
        }

        /*
         * Hard-polling can be problematic and is used only to keep the example short
         */
        usleep(loop_delay_ms * 1000);
    }

    printf("Done...\n");
    return 0;
}

#endif  // __GNUC__
