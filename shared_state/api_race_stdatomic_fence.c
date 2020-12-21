/**
 * @file api_race_stdatomic_fence.c
 *
 * Trying to fix an API race using C11's atomic fence.
 *
 * http://irl.cs.ucla.edu/~yingdi/web/paperreading/whymb.2010.06.07c.pdf
 * https://gcc.gnu.org/wiki/Atomic/GCCMM/AtomicSync
 * https://en.cppreference.com/w/c/language/atomic
 * https://en.cppreference.com/w/c/atomic/atomic_thread_fence
 * https://en.cppreference.com/w/c/atomic/memory_order
 * https://preshing.com/20120515/memory-reordering-caught-in-the-act/
 * https://preshing.com/20131125/acquire-and-release-fences-dont-work-the-way-youd-expect/
 * https://preshing.com/20130922/acquire-and-release-fences/
 * https://stackoverflow.com/questions/51315186/is-atomic-thread-fencememory-order-release-different-from-using-memory-order-a
 * https://stackoverflow.com/questions/19689872/c11-memory-fence-usage
 * https://stackoverflow.com/questions/14167767/what-is-the-difference-between-using-explicit-fences-and-stdatomic
 * https://stackoverflow.com/questions/13632344/understanding-c11-memory-fences
 * https://stackoverflow.com/questions/25478029/does-atomic-thread-fencememory-order-seq-cst-have-the-semantics-of-a-full-memo
 * https://stackoverflow.com/questions/14581090/how-to-correctly-use-stdatomic-signal-fence
 * https://devblogs.microsoft.com/oldnewthing/20081003-00/?p=20663
 * https://bartoszmilewski.com/2008/12/01/c-atomics-and-memory-ordering/
 * https://mintomic.github.io/lock-free/memory-fences/
 */

#ifdef __STDC_NO_ATOMICS__

#include <stdio.h>

int main(void)
{
    printf("Example requires a C compiler with atomics (C11 or later)\n");
    return -1;
}

#else

#include <stdio.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <unistd.h>

static atomic_bool event_flag = true;
static atomic_int event_state;

int main(void)
{
    printf("Starting...\n");
    __useconds_t loop_delay_ms = 100;

    while (1)
    {
        if (event_flag)
        {
            /*
             * As written, this is impossible to synchronize.
             * Although access to each individual variable is thread safe,
             * the thread could be interrupted *between* accesses.
             * This will not be reported by the thread sanitizer!
             */
            int local_event_state = event_state;
            printf("Event state: %d\n", local_event_state);
        }

        /*
         * Hard-polling can be problematic and is used only to keep the example short
         */
        usleep(loop_delay_ms * 1000);
    }

    printf("Done...\n");
    return 0;
}

#endif  // __STDC_NO_ATOMICS__
