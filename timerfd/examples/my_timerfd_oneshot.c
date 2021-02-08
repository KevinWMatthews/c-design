/**
 * @file my_timerfd_oneshor.c
 */
#include "my_timerfd.h"
#include <stdio.h>

int main(void)
{
    printf("Starting...\n");
    my_timerfd_t fd_timer = my_timerfd_open(MY_TIMERFD_FLAGS_BLOCKING);

    printf("Waiting for timeout...\n");
    // my_timerfd_start_oneshot_s(fd_timer, 1);
    // my_timerfd_start_oneshot_ms(fd_timer, 1);
    // my_timerfd_start_oneshot_us(fd_timer, 1);
    my_timerfd_start_oneshot_ns(fd_timer, 1);

    // The timer only executes once, even if the timeout is extremely short
    uint64_t n_timeouts = my_timerfd_read(fd_timer);
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);

    // The timer has stopped, so any further read will block
    /*
    printf("Blocking read...\n");
    n_timeouts = my_timerfd_read(fd_timer);
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);
    // */

    my_timerfd_close(fd_timer);
    printf("Done\n");
    return 0;
}
