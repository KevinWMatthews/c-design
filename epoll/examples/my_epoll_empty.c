/**
 * @file my_epoll_empty.c
 * Simplest possible intro to epoll: no events; only the epoll timeout.
 */
#include "my_epoll.h"
#include <assert.h>
#include <stdio.h>

#define EVENT_LIST_LEN     10

int main(void)
{
    printf("Starting...\n");
    my_epoll_t epfd = my_epoll_open();

    struct epoll_event event_list[EVENT_LIST_LEN] = {0};
    size_t event_list_len = sizeof(event_list) / sizeof(*event_list);
    int timeout_ms = 1000;
    while (1)
    {
        int n_events = my_epoll_wait(epfd, event_list, event_list_len, timeout_ms);
        if (n_events == 0 && timeout_ms > 0)
        {
            printf("Epoll timeout occurred\n");
            continue;
        }

        // No events in this example
        assert(n_events == 0);
    }

    my_epoll_close(epfd);
    printf("Done\n");
    return 0;
}
