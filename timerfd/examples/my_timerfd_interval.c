/**
 * @file my_timerfd_interval.c
 */
#include "my_timerfd.h"
#include <stdio.h>

int main(void)
{
    size_t timeout_count = 0;
    printf("Starting...\n");
    my_timerfd_t fd_timer = my_timerfd_open(MY_TIMERFD_FLAGS_BLOCKING);

    printf("Starting interval timer...\n");
    // my_timerfd_start_interval_s(fd_timer, 1);
    // my_timerfd_start_interval_ms(fd_timer, 1);
    // my_timerfd_start_interval_us(fd_timer, 1);
    my_timerfd_start_interval_ns(fd_timer, 1);

    // If timeout interval is very short, the timer could expire multiple times before
    // the read() system call opens the file descriptor.
    do
    {
        uint64_t n_timeouts = my_timerfd_read(fd_timer);
        printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);
        timeout_count += n_timeouts;
    } while (timeout_count < 10);

    my_timerfd_stop(fd_timer);

    // The timer is stopped, so any further read will block
    /*
    printf("Blocking read...\n");
    uint64_t n_timeouts = my_timerfd_read(fd_timer);
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);
    // */

    my_timerfd_close(fd_timer);
    printf("Done\n");
    return 0;
}
