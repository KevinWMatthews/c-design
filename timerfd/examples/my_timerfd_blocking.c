/**
 * @file my_timerfd_blocking.c
 */
#include "my_timerfd.h"
#include <stdio.h>

int main(void)
{
    printf("Starting...\n");
    my_timerfd_t fd_timer = my_timerfd_open(MY_TIMERFD_FLAGS_BLOCKING);

    printf("Waiting for timeout...\n");
    my_timerfd_start_oneshot_s(fd_timer, 1);
    uint64_t n_timeouts = my_timerfd_read(fd_timer);
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);

    /*
    printf("Blocking read...\n");
    n_timeouts = my_timerfd_read(fd_timer);
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);
    // */

    my_timerfd_close(fd_timer);
    printf("Done\n");
    return 0;
}
