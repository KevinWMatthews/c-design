/**
 * @file my_eventfd_blocking_multi.c
 */
#include "my_eventfd.h"
#include "my_pthread.h"
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>
#include <assert.h>

void *writer_thread(void *param)
{
    printf("%s: Entering\n", __func__);
    my_eventfd_t efd = *(my_eventfd_t *)param;

    printf("%s: Sleeping...\n", __func__);
    sleep(3);

    uint64_t value = 3;
    printf("%s: Writing to eventfd: '%" PRIu64 "'\n", __func__, value);
    my_eventfd_write(efd, value);

    printf("%s: Exiting\n", __func__);
    return NULL;
}

void *reader_thread(void *param)
{
    printf("%s: Entering\n", __func__);
    my_eventfd_t efd = *(my_eventfd_t *)param;

    printf("%s: Blocking read...\n", __func__);
    uint64_t value = my_eventfd_read(efd);
    printf("Read from eventfd: '%" PRIu64 "'\n", value);

    printf("%s: Exiting\n", __func__);
    return NULL;
}

int main(void)
{
    printf("Starting...\n");

    my_eventfd_t efd = my_eventfd_open(0, MY_EVENTFD_FLAGS_BLOCKING);

    pthread_t reader_handle = my_pthread_create_noattr(reader_thread, &efd);
    pthread_t writer_handle = my_pthread_create_noattr(writer_thread, &efd);

    my_pthread_join_noarg(writer_handle);
    my_pthread_join_noarg(reader_handle);

    my_eventfd_close(efd);

    printf("Done\n");
    return 0;
}
