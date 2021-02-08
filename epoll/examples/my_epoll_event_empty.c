/**
 * @file my_epoll_event_empty.c
 */
#include "my_epoll_event.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    printf("Starting...\n");
    my_epoll_t epfd = my_epoll_open();

    int timeout_ms = 1000;
    while (1)
    {
        struct my_epoll_event_t* this_event = my_epoll_event_wait_single(epfd, timeout_ms);
        if (this_event == NULL && timeout_ms > 0)
        {
            printf("Epoll timeout occurred\n");
            continue;
        }

        // No events in this example
        assert(!this_event);
    }

    my_epoll_close(epfd);
    printf("Done\n");
    return 0;
}
