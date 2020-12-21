/**
 * @file my_epoll_event.h
 * Opinionated API for processing epoll events.
 * @{
 */
#ifndef MY_EPOLL_EVENT_H_INCLUDED
#define MY_EPOLL_EVENT_H_INCLUDED

#include "my_epoll.h"

typedef struct my_epoll_event_data_s
{
    void *ptr;
} my_epoll_event_data_t;

typedef void (*my_epoll_event_process_fp)(my_epoll_t fd_epoll,
    int fd_event,
    my_epoll_event_data_t data);

struct my_epoll_event_t
{
    int fd_event;
    my_epoll_event_data_t data;
    my_epoll_event_process_fp process;
};

void my_epoll_event_setup(struct my_epoll_event_t *event,
    int fd_event,
    my_epoll_event_data_t data,
    my_epoll_event_process_fp process);

void my_epoll_event_add_input(my_epoll_t fd_epoll,
    enum my_epoll_flags_t flags,
    struct my_epoll_event_t *my_event);

void my_epoll_event_add_output(my_epoll_t fd_epoll,
    enum my_epoll_flags_t flags,
    struct my_epoll_event_t *my_event);

void my_epoll_event_delete(my_epoll_t fd_epoll, struct my_epoll_event_t *my_event);

// implement when needed
// void my_epoll_event_delete(my_epoll_t fd_epoll, struct my_epoll_event_t *my_event);

// For convenience in example apps
struct my_epoll_event_t *my_epoll_event_wait_single(my_epoll_t fd_epoll, int timeout_ms);

void my_epoll_event_process(my_epoll_t fd_epoll, struct my_epoll_event_t *event);

#endif

/** @} */
