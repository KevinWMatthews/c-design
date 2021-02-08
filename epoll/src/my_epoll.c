/**
 * @file my_epoll.c
 */
#include "my_epoll.h"
#include <stddef.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>

// TODO make CLOEXEC an option
my_epoll_t my_epoll_open(void)
{
    int fd = epoll_create1(EPOLL_CLOEXEC);
    assert(fd != -1);
    my_epoll_t my_epoll = {
        .fd = fd,
    };
    return my_epoll;
}

void my_epoll_close(my_epoll_t fd_epoll)
{
    int err = close(fd_epoll.fd);
    assert(!err);
}

int my_epoll_wait(my_epoll_t fd_epoll,
    struct epoll_event* event_list,
    int event_list_len,
    int timeout_ms)
{
    assert(event_list);

    int n_events;
    while (1)
    {
        n_events = epoll_wait(fd_epoll.fd, event_list, event_list_len, timeout_ms);
        if (n_events == -1)
        {
            if (errno == EINTR)
            {
                // Signals can be delivered to blocking system calls,
                // causing the function to return EINTR.
                // This can occur with SIGINT, SIGSTOP (e.g. debugger placing breakpoints), etc.
                // TODO can we tell which signal occurred? I don't think so; use epoll_pwait() instead
                // In a single-threaded application, the behavior is predictable because there is
                // only a single blocking system to be woken.
                // In a multi-threaded application, the behavior is more complex.
                // The system can deliver the signal to any thread that has not blocked the signal.
                continue;
            }
            assert(n_events != -1);
        }
        // For 0 events, a timeout occurred.
        return n_events;
    }
}

int my_epoll_ctl(my_epoll_t fd_epoll,
    int fd_event,
    enum my_epoll_opcode_t opcode,
    struct epoll_event* event)
{
    assert(event);
    return epoll_ctl(fd_epoll.fd, opcode, fd_event, event);
}

void my_epoll_control(my_epoll_t fd_epoll,
    int fd_event,
    enum my_epoll_opcode_t opcode,
    int flags,
    epoll_data_t data)
{
    struct epoll_event event = {
        .events = flags,
        .data = data,
    };
    int err = my_epoll_ctl(fd_epoll, opcode, fd_event, &event);
    assert(!err);
}

void my_epoll_add_input(my_epoll_t fd_epoll,
    int fd_event,
    enum my_epoll_flags_t flags,
    epoll_data_t data)
{
    struct epoll_event event = {
        .events = EPOLLIN | flags,
        .data = data,
    };
    int err = my_epoll_ctl(fd_epoll, fd_event, MY_EPOLL_OPCODE_ADD, &event);
    assert(!err);
}

void my_epoll_add_output(my_epoll_t fd_epoll,
    enum my_epoll_flags_t flags,
    int fd_event,
    epoll_data_t data)
{
    struct epoll_event event = {
        .events = EPOLLOUT | flags,
        .data = data,
    };
    int err = my_epoll_ctl(fd_epoll, fd_event, MY_EPOLL_OPCODE_ADD, &event);
    assert(!err);
}

void my_epoll_delete(my_epoll_t fd_epoll, int fd_event)
{
    // The epoll_event struct has no effect - the event will no longer occur
    int err = my_epoll_ctl(fd_epoll, fd_event, MY_EPOLL_OPCODE_DELETE, NULL);
    assert(!err);
}

void my_epoll_modify(my_epoll_t fd_epoll, int fd_event, int new_flags, epoll_data_t new_data)
{
    struct epoll_event event = {
        .events = new_flags,
        .data = new_data,
    };
    my_epoll_ctl(fd_epoll, fd_event, MY_EPOLL_OPCODE_MODIFY, &event);
}
