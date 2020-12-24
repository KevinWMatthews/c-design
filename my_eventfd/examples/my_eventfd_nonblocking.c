/**
 * @file my_eventfd_nonblocking.c
 */
#include "my_eventfd.h"
#include <stdio.h>
#include <inttypes.h>

int main(void)
{
    printf("Starting...\n");

    my_eventfd_t efd = my_eventfd_open(0, MY_EVENTFD_FLAGS_NONBLOCKING);

    uint64_t write_value = 3;
    printf("Writing to eventfd: '%" PRIu64 "'\n", write_value);
    my_eventfd_write(efd, write_value);

    printf("Reading from eventfd...\n");
    uint64_t read_value = my_eventfd_read(efd);
    printf("Read from eventfd: '%" PRIu64 "'\n", read_value);

    // If the eventfd's value is 0, read() will fail
    printf("Blocking read...\n");
    // This wrapper library returns 0 if the eventfd read would block
    read_value = my_eventfd_read(efd);
    printf("Read from eventfd: '%" PRIu64 "'\n", read_value);

    my_eventfd_close(efd);

    printf("Done\n");
    return 0;
}
