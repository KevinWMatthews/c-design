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

    uint64_t write_value = 3;
    printf("Writing to eventfd: '%" PRIu64 "'\n", write_value);
    ssize_t n_written = write(efd, &write_value, sizeof(write_value));
    assert(n_written != -1);
    assert(n_written == sizeof(write_value));

    printf("Reading from eventfd...\n");
    uint64_t read_value = 0;
    ssize_t n_read = read(efd, &read_value, sizeof(read_value));
    assert(n_read != -1);
    assert(n_read == sizeof(read_value));
    printf("Read from eventfd: '%" PRIu64 "'\n", read_value);

    // If the eventfd's value is 0, read() will fail
    printf("Read would block...\n");
    read_value = 0;
    n_read = read(efd, &read_value, sizeof(read_value));
    assert(n_read == -1);
    assert(errno == EAGAIN || errno == EWOULDBLOCK);
    printf("Value not read\n");

    err = close(efd);
    assert(!err);

    printf("Done\n");
    return 0;
}
