/**
 * @file eventfd_blocking.c
 */
#include <sys/eventfd.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>

int main(void)
{
    printf("Starting...\n");
    int err;

    int efd = eventfd(0, 0);
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

    // If the eventfd's value is 0, read() will block forever
    /*
    printf("Blocking read...\n");
    value = 0;
    n_read = read(efd, &value, sizeof(value));
    assert(n_read != -1);
    assert(n_read == sizeof(value));
    printf("Read from eventfd: '%" PRIu64 "'\n", value);
    // */

    err = close(efd);
    assert(!err);

    printf("Done\n");
    return 0;
}
