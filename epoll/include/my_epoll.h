/**
 * @file my_epoll.h
 * Thin wrapper around Linux's sys/epoll API.
 * @{
 */
#ifndef MY_EPOLL_H_INCLUDED
#define MY_EPOLL_H_INCLUDED

#include <sys/epoll.h>

typedef struct my_epoll_s
{
    int fd;
} my_epoll_t;

// See enum EPOLL_EVENTS for more options
// Interesting things are:
// EPOLLRDHUP
// EPOLLERR
// TODO can't find EPOLLMSG in the docs
// EPOLLET | EPOLLIN | EPOLLOUT
enum my_epoll_flags_t
{
    MY_EPOLL_FLAGS_LEVEL = 0,
    MY_EPOLL_FLAGS_LEVEL_ONESHOT = EPOLLONESHOT,
    MY_EPOLL_FLAGS_EDGE = EPOLLET,
    MY_EPOLL_FLAGS_EDGE_ONESHOT = EPOLLET | EPOLLONESHOT,
};

enum my_epoll_opcode_t
{
    MY_EPOLL_OPCODE_ADD = EPOLL_CTL_ADD,
    MY_EPOLL_OPCODE_DELETE = EPOLL_CTL_DEL,
    MY_EPOLL_OPCODE_MODIFY = EPOLL_CTL_MOD,
};

my_epoll_t my_epoll_open(void);

// This deletes all associated events
void my_epoll_close(my_epoll_t);

// Read the docs for behavior if the number of actual events exceeds the length of the event list.
// To wait forever, set the timeout to -1.
int my_epoll_wait(my_epoll_t fd_epoll,
    struct epoll_event *event_list,
    int event_list_len,
    int timeout_ms);

int my_epoll_ctl(my_epoll_t fd_epoll,
    int fd_event,
    enum my_epoll_opcode_t opcode,
    struct epoll_event *event);
// TODO double-check lifetime
// Generic
void my_epoll_control(my_epoll_t fd_epoll,
    int fd_event,
    enum my_epoll_opcode_t opcode,
    int flags,
    epoll_data_t data);

void my_epoll_add_input(my_epoll_t fd_epoll,
    int fd_event,
    enum my_epoll_flags_t flags,
    epoll_data_t data);

void my_epoll_add_output(my_epoll_t fd_epoll,
    enum my_epoll_flags_t flags,
    int fd_event,
    epoll_data_t data);

void my_epoll_delete(my_epoll_t fd_epoll, int fd_event);

// TODO Does this actually associate new data or just the flags?
void my_epoll_modify(my_epoll_t fd_epoll, int fd_event, int new_flags, epoll_data_t new_data);

#endif

/** @} */
