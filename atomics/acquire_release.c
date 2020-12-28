/**
 * @file acquire_release.c
 * Intro to acquire-release semantics.
 *TODO re-watch a few videos on this
 * Come up with a better example. Should this be a spin lock?
 * This works in a limited number of cases.
 */
#include "my_pthread.h"
#include <stdatomic.h>
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

struct thread_params_t
{
    // Access to the value is unsafe
    int value;
    // The flag is not atomic but individual accesses are
    bool ready_flag;
};

void *producer_thread(void *param)
{
    printf("%s: Entering\n", __func__);
    struct thread_params_t *shared_memory = param;
    sleep(2);
    shared_memory->value = 42;
    // "Release" any pending writes to memory
    atomic_store_explicit(&shared_memory->ready_flag, true, __ATOMIC_RELEASE);
    printf("%s: Exiting\n", __func__);
    return NULL;
}

void *consumer_thread(void *param)
{
    printf("%s: Entering\n", __func__);
    struct thread_params_t *shared_memory = param;
    // how does the optimizer tread while (1) vs while (!flag)?
    // this is a spinlock of sorts?
    // Is there a way to do this without polling?
    while (1)
    {
        // "Acquire" all memory
        if (atomic_load_explicit(&shared_memory->ready_flag, __ATOMIC_ACQUIRE))
        {
            break;
        }
        usleep(10);
    }
    int value = shared_memory->value;
    printf("%s: Value: %d\n", __func__, value);
    printf("%s: Exiting\n", __func__);
    return NULL;
}

int main(void)
{
    struct thread_params_t shared_memory = {0};
    pthread_t producer_handle = my_pthread_create_noattr(producer_thread, &shared_memory);
    pthread_t consumer_handle = my_pthread_create_noattr(consumer_thread, &shared_memory);

    my_pthread_join_noarg(producer_handle);
    my_pthread_join_noarg(consumer_handle);
    return 0;
}
