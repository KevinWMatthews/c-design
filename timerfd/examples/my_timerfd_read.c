/**
 * @file my_timerfd_read.c
 */
#include "my_timerfd.h"
#include <stdio.h>

int main(void)
{
    printf("Starting...\n");
    // enum my_timerfd_flags_t flags = MY_TIMERFD_FLAGS_BLOCKING;
    enum my_timerfd_flags_t flags = MY_TIMERFD_FLAGS_NONBLOCKING;
    my_timerfd_t fd_timer = my_timerfd_open(flags);

    printf("Starting one-shot timer...\n");
    my_timerfd_start_oneshot_s(fd_timer, 3);

    // If timerfd is blocking, blocks until the timer has expired
    // If timerfd is non-blocking, ?
    uint64_t n_timeouts = my_timerfd_read(fd_timer);
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);

    my_timerfd_close(fd_timer);
    printf("Done\n");
    return 0;
}
