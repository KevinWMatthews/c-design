/**
 * @file hard_poll_no_queue.c
 */

#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

/*
 * Flags that are set by an external event source
 */
static volatile atomic_bool event1_flag;
static volatile atomic_bool event2_flag;

int main(void)
{
    printf("Starting...\n");
    __useconds_t loop_delay_ms = 100;

    while (1)
    {
        /*
         * This loop structure imposes an artificial priority between events.
         * This only manifests itself if two events occur during the sleep period.
         */
        if (event1_flag)
        {
            // do stuff
        }
        if (event2_flag)
        {
            // do stuff
        }

        /*
         * Must sleep to avoid eating all the CPU.
         * However, this can miss events that occur more frequently than the sleep period.
         */
        usleep(loop_delay_ms * 1000);
    }

    printf("Done...\n");
    return 0;
}
