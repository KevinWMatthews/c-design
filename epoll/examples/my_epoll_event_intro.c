/**
 * @file my_epoll_event_intro.c
 */
#include "my_epoll_event.h"
#include "my_timerfd.h"
#include <stdio.h>
#include <inttypes.h>

static void on_timer_event(my_epoll_t fd_epoll, int fd_event, my_epoll_event_data_t data)
{
    printf("Timer event received\n");
    // Alternate
    /*
    my_timerfd_t tfd = {
        .fd = fd_event,
    };
    uint64_t n_timeouts = my_timerfd_read(tfd);
    // */

    // Alternate
    /*
    uint64_t n_timeouts = my_timerfd_read((my_timerfd_t){fd_event});
    // */

    // Alternate
    //*
    my_timerfd_t* tfd = data.ptr;
    uint64_t n_timeouts = my_timerfd_read(*tfd);
    // */

    printf("N timeouts: %" PRIu64 "\n", n_timeouts);
}

int main(void)
{
    printf("Starting...\n");
    my_epoll_t epfd = my_epoll_open();

    my_timerfd_t tfd = my_timerfd_open(MY_TIMERFD_FLAGS_NONBLOCKING);

    struct my_epoll_event_t timer_event = {0};
    my_epoll_event_data_t timer_event_data = {
        .ptr = &tfd,
    };
    my_epoll_event_setup(&timer_event, tfd.fd, on_timer_event, timer_event_data);
    my_epoll_event_add_input(epfd, MY_EPOLL_FLAGS_LEVEL, &timer_event);

    my_timerfd_start_interval_s(tfd, 1);

    while (1)
    {
        int timeout_ms = -1;
        struct my_epoll_event_t* this_event = my_epoll_event_wait_single(epfd, timeout_ms);
        if (this_event == NULL && timeout_ms > 0)
        {
            printf("Epoll timeout occurred\n");
            continue;
        }

        my_epoll_event_process(epfd, this_event);
    }

    my_timerfd_close(tfd);
    my_epoll_close(epfd);
    printf("Done\n");
    return 0;
}
