/**
 * @file my_eventfd.h
 * @{
 */
#ifndef MY_EVENTFD_H_INCLUDED
#define MY_EVENTFD_H_INCLUDED

#include <sys/eventfd.h>

typedef struct my_eventfd_s
{
    int fd;
} my_eventfd_t;

enum my_eventfd_flags_t
{
    MY_EVENTFD_FLAGS_BLOCKING = 0,
    MY_EVENTFD_FLAGS_NONBLOCKING = EFD_NONBLOCK,
};

my_eventfd_t my_eventfd_open(unsigned int initial_value, enum my_eventfd_flags_t flags);
void my_eventfd_close(my_eventfd_t fd_event);
void my_eventfd_write(my_eventfd_t fd_event, uint64_t value);
uint64_t my_eventfd_read(my_eventfd_t fd_event);
void my_eventfd_clear(my_eventfd_t fd_event);

#endif

/** @} */
