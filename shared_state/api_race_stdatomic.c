/**
 * @file api_race_stdatomic.c
 *
 * Demonstrating an API race with C11's atomics.
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
