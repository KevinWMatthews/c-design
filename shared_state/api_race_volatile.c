/**
 * @file api_race_volatile.c
 */

#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// TODO volatile prevents some forms of optimization?
static volatile bool event_flag = true;
static volatile int event_state;

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
