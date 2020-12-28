/**
 * @file sys_epoll_empty.c
 * Simplest possible intro to epoll: no events; only the epoll timeout.
 */
#include <sys/epoll.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define EVENT_LIST_LEN     10

int main(void)
{
    int err;
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    assert(epfd != -1);

    struct epoll_event event_list[EVENT_LIST_LEN] = {0};
    size_t event_list_len = sizeof(event_list) / sizeof(*event_list);
    // -1 == no timeout
    // 0 == timeout immediately
    int timeout_ms = 1000;
    while (1)
    {
        int n_events = epoll_wait(epfd, event_list, event_list_len, timeout_ms);
        if (n_events == -1)
        {
            if (errno == EINTR)
            {
                // epoll() returns failure if interrupted by a signal
                // gdb can't place breakpoints at runtime,
                // so debuggers typically send SIGSTOP
                continue;
            }
        }
        assert(n_events != -1);

        if (n_events == 0 && timeout_ms > 0)
        {
            printf("Epoll timeout occurred\n");
            continue;
        }
        // Process events in list
    }

    err = close(epfd);
    assert(!err);
    return 0;
}
