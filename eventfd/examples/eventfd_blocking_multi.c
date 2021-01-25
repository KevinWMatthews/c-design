/**
 * @file eventfd_blocking_multi.c
 */
#include <sys/eventfd.h>
#include <stdio.h>
#include <pthread.h>
#include <inttypes.h>
#include <unistd.h>
#include <assert.h>

void *writer_thread(void *param)
{
    printf("%s: Entering\n", __func__);
    int efd = *(int *)param;

    printf("%s: Sleeping...\n", __func__);
    sleep(3);

    uint64_t value = 3;
    printf("%s: Writing to eventfd: '%" PRIu64 "'\n", __func__, value);
    ssize_t n_written = write(efd, &value, sizeof(value));
    assert(n_written != -1);
    assert(n_written == sizeof(value));

    printf("%s: Exiting\n", __func__);
    return NULL;
}

void *reader_thread(void *param)
{
    printf("%s: Entering\n", __func__);
    int efd = *(int *)param;

    printf("%s: Blocking read...\n", __func__);
    uint64_t value = 0;
    ssize_t n_read = read(efd, &value, sizeof(value));
    assert(n_read != -1);
    assert(n_read == sizeof(value));
    printf("Read from eventfd: '%" PRIu64 "'\n", value);

    printf("%s: Exiting\n", __func__);
    return NULL;
}

int main(void)
{
    printf("Starting...\n");
    int err;

    int efd = eventfd(0, 0);
    assert(efd != -1);

    pthread_t reader_handle;
    err = pthread_create(&reader_handle, NULL, reader_thread, &efd);
    assert(!err);

    pthread_t writer_handle;
    err = pthread_create(&writer_handle, NULL, writer_thread, &efd);
    assert(!err);

    err = pthread_join(writer_handle, NULL);
    assert(!err);
    err = pthread_join(reader_handle, NULL);
    assert(!err);

    err = close(efd);
    assert(!err);

    printf("Done\n");
    return 0;
}
