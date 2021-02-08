/**
 * @file my_timerfd_remaining.c
 */
#include "my_timerfd.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Starting...\n");
    // Non-blocking timer so this thread can work while the timer is running
    my_timerfd_t fd_timer = my_timerfd_open(MY_TIMERFD_FLAGS_NONBLOCKING);

    my_timerfd_start_interval_s(fd_timer, 10);
    sleep(1);
    struct timespec remaining = my_timerfd_remaining(fd_timer);
    printf("Remaining time: %ld s, %9ld ns\n", remaining.tv_sec, remaining.tv_nsec);

    my_timerfd_stop(fd_timer);
    remaining = my_timerfd_remaining(fd_timer);
    printf("Remaining time: %ld s, %9ld ns\n", remaining.tv_sec, remaining.tv_nsec);

    my_timerfd_close(fd_timer);
    printf("Done\n");
    return 0;
}
