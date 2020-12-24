/**
 * @file eventfd_nonblocking.c
 */
#include <sys/eventfd.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <errno.h>

int main(void)
{
    printf("Starting...\n");
    int err;

    int efd = eventfd(0, EFD_NONBLOCK);
    assert(efd != -1);

    uint64_t value = 3;
    printf("Writing to eventfd: '%" PRIu64 "'\n", value);
    ssize_t n_written = write(efd, &value, sizeof(value));
    assert(n_written != -1);
    assert(n_written == sizeof(value));

    printf("Reading from eventfd...\n");
    value = 0;
    ssize_t n_read = read(efd, &value, sizeof(value));
    assert(n_read != -1);
    assert(n_read == sizeof(value));
    printf("Read from eventfd: '%" PRIu64 "'\n", value);

    // If the eventfd's value is 0, read() will fail
    printf("Read would block...\n");
    value = 0;
    n_read = read(efd, &value, sizeof(value));
    assert(n_read == -1);
    assert(errno == EAGAIN || errno == EWOULDBLOCK);
    printf("Value not read\n");

    err = close(efd);
    assert(!err);

    printf("Done\n");
    return 0;
}
