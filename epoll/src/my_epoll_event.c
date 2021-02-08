/**
 * @file my_epoll_event.c
 */
#include "my_epoll_event.h"
#include <assert.h>
#include <stddef.h>

void my_epoll_event_setup(struct my_epoll_event_t* event,
    int fd_event,
    my_epoll_event_process_fp process,
    my_epoll_event_data_t data)
{
    assert(event);
    assert(process);
    event->fd_event = fd_event;
    event->process = process;
    event->data = data;
}

void my_epoll_event_add_input(my_epoll_t fd_epoll,
    enum my_epoll_flags_t flags,
    struct my_epoll_event_t* my_event)
{
    assert(my_event);
    // Erase type
    epoll_data_t data = {.ptr = my_event};
    my_epoll_add_input(fd_epoll, my_event->fd_event, flags, data);
}

void my_epoll_event_add_output(my_epoll_t fd_epoll,
    enum my_epoll_flags_t flags,
    struct my_epoll_event_t* my_event)
{
    assert(my_event);
    // Erase type
    epoll_data_t data = {.ptr = my_event};
    my_epoll_add_output(fd_epoll, my_event->fd_event, flags, data);
}

void my_epoll_event_delete(my_epoll_t fd_epoll, struct my_epoll_event_t* my_event)
{
    assert(my_event);
    my_epoll_delete(fd_epoll, my_event->fd_event);
}

struct my_epoll_event_t* my_epoll_event_wait_single(my_epoll_t fd_epoll, int timeout_ms)
{
    struct epoll_event event_list[1] = {0};
    int event_list_len = sizeof(event_list) / sizeof(*event_list);
    int n_events = my_epoll_wait(fd_epoll, event_list, event_list_len, timeout_ms);
    assert(n_events != -1);
    if (n_events == 0)  // This indicates a timeout
    {
        return NULL;
    }
    struct epoll_event* this_event = &event_list[0];
    // Recover type
    struct my_epoll_event_t* my_event = this_event->data.ptr;
    return my_event;
}

void my_epoll_event_process(my_epoll_t fd_epoll, struct my_epoll_event_t* event)
{
    if (!event)
    {
        // May have been a timeout event
        return;
    }
    event->process(fd_epoll, event->fd_event, event->data);
}
