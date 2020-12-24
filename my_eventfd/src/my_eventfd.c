/**
 * @file my_eventfd.c
 */
#include "my_eventfd.h"
#include <unistd.h>
#include <assert.h>
#include <errno.h>

my_eventfd_t my_eventfd_open(unsigned int initial_value, enum my_eventfd_flags_t flags)
{
    flags |= EFD_CLOEXEC;
    int fd = eventfd(initial_value, flags);
    assert(fd != -1);
    my_eventfd_t my_event = {
        .fd = fd,
    };
    return my_event;
}

void my_eventfd_close(my_eventfd_t fd_event)
{
    int err = close(fd_event.fd);
    assert(!err);
}

void my_eventfd_write(my_eventfd_t fd_event, uint64_t value)
{
    size_t bytes_to_write = sizeof(value);
    ssize_t bytes_written = write(fd_event.fd, &value, bytes_to_write);
    assert(bytes_written == bytes_to_write);
}

uint64_t my_eventfd_read(my_eventfd_t fd_event)
{
    uint64_t value = 0;
    size_t bytes_to_read = sizeof(value);
    ssize_t ret = read(fd_event.fd, &value, bytes_to_read);
    if (ret == -1)
    {
        if (errno == EAGAIN || errno == EWOULDBLOCK)
        {
            return 0;
        }
    }
    assert(ret == bytes_to_read);
    return value;
}

void my_eventfd_clear(my_eventfd_t fd_event)
{
    my_eventfd_read(fd_event);
}
