/**
 * @file timerfd_blocking.c
 */
#include <sys/timerfd.h>
#include <inttypes.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    printf("Starting...\n");
    int err;

    int clock_id = CLOCK_REALTIME;  // TODO research different clock types
    int flags = 0;
    int tfd = timerfd_create(clock_id, flags);
    assert(tfd != -1);

    struct itimerspec new_timerspec = {
        // Value for initial timeout. If set to zero, the timer will never expire!
        .it_value = {
            .tv_sec = 1,
            .tv_nsec = 0,
        },
        // Value for repeated timeouts. May be zero.
        .it_interval = {
            .tv_sec = 0,
            .tv_nsec = 0,
        },
    };
    struct itimerspec old_timerspec = {0};
    flags = 0;
    // This starts the timer
    err = timerfd_settime(tfd, flags, &new_timerspec, &old_timerspec);
    assert(!err);

    // read() will block until the timer expires
    printf("Waiting for timeout...\n");
    uint64_t n_timeouts = 0;
    err = read(tfd, &n_timeouts, sizeof(n_timeouts));
    assert(err == sizeof(uint64_t));
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);

    // if the timer is one-shot, this will block forever!
    /*
    n_timeouts = 0;
    printf("Blocking read...\n");
    err = read(tfd, &n_timeouts, sizeof(n_timeouts));
    assert(!err);
    printf("Timer timed out '%" PRIu64 "' times\n", n_timeouts);
    // */

    err = close(tfd);
    assert(!err);

    printf("Done\n");
    return 0;
}
