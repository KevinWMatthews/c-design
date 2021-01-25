/**
 * @file my_eventfd_sem_sem.h
 * Semaphore eventfd are largely identical to a traditional eventfd.
 * However, instead of reading and resetting the entire value,
 * semaphore eventfd decrement the value by 1.
 * @{
 */
#ifndef MY_EVENTFD_SEM_H_INCLUDED
#define MY_EVENTFD_SEM_H_INCLUDED

#include <sys/eventfd.h>

typedef struct my_eventfd_sem_s
{
    int fd;
} my_eventfd_sem_t;

enum my_eventfd_sem_flags_t
{
    MY_EVENTFD_SEM_FLAGS_BLOCKING = 0,
    MY_EVENTFD_SEM_FLAGS_NONBLOCKING = EFD_NONBLOCK,
};

my_eventfd_sem_t my_eventfd_sem_open(unsigned int initial_value, enum my_eventfd_sem_flags_t flags);
void my_eventfd_sem_close(my_eventfd_sem_t fd_event);
void my_eventfd_sem_write(my_eventfd_sem_t fd_event, uint64_t value);
// TODO if the value is 0:
// blocking eventfd will block
// non-blocking eventfd will return EAGAIN
uint64_t my_eventfd_sem_read(my_eventfd_sem_t fd_event);
void my_eventfd_sem_clear(my_eventfd_sem_t fd_event);

#endif

/** @} */
