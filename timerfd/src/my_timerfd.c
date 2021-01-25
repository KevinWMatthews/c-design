/**
 * @file my_timerfd.c
 */
#include "my_timerfd.h"
#include <assert.h>
#include <unistd.h>

my_timerfd_t my_timerfd_open(enum my_timerfd_flags_t flags)
{
    int clock_id = CLOCK_REALTIME;
    int fd = timerfd_create(clock_id, flags | TFD_CLOEXEC);
    assert(fd != -1);
    my_timerfd_t my_timerfd = {
        .fd = fd,
    };
    return my_timerfd;
}

void my_timerfd_close(my_timerfd_t fd_timer)
{
    int err = close(fd_timer.fd);
    assert(!err);
}

void my_timerfd_start_oneshot_s(my_timerfd_t fd_timer, time_t seconds)
{
    struct itimerspec timerspec = {
        .it_value = {
            .tv_sec = seconds,
            .tv_nsec = 0,
        },
        .it_interval = {0},
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

void my_timerfd_start_oneshot_ms(my_timerfd_t fd_timer, time_t milliseconds)
{
    assert(milliseconds < 1000);    // TODO verify
    struct itimerspec timerspec = {
        .it_value = {
            .tv_sec = 0,
            .tv_nsec = milliseconds * 1000 * 1000,
        },
        .it_interval = {0},
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

void my_timerfd_start_oneshot_us(my_timerfd_t fd_timer, time_t microseconds)
{
    assert(microseconds < 1000 * 1000);    // TODO verify
    struct itimerspec timerspec = {
        .it_value = {
            .tv_sec = 0,
            .tv_nsec = microseconds * 1000,
        },
        .it_interval = {0},
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

void my_timerfd_start_oneshot_ns(my_timerfd_t fd_timer, time_t nanoseconds)
{
    assert(nanoseconds < 1000 * 1000 * 1000);   // TODO verify
    struct itimerspec timerspec = {
        .it_value = {
            .tv_sec = 0,
            .tv_nsec = nanoseconds,
        },
        .it_interval = {0},
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}


void my_timerfd_start_interval_s(my_timerfd_t fd_timer, time_t seconds)
{
    struct itimerspec timerspec = {
        .it_value = {0},
        .it_interval = {
            .tv_sec = seconds,
            .tv_nsec = 0,
        }
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

void my_timerfd_start_interval_ms(my_timerfd_t fd_timer, time_t milliseconds)
{
    assert(milliseconds < 1000);    // TODO verify
    struct itimerspec timerspec = {
        .it_value = {0},
        .it_interval = {
            .tv_sec = 0,
            .tv_nsec = milliseconds * 1000 * 1000,
        },
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

void my_timerfd_start_interval_us(my_timerfd_t fd_timer, time_t microseconds)
{
    assert(microseconds < 1000 * 1000);    // TODO verify
    struct itimerspec timerspec = {
        .it_value = {0},
        .it_interval = {
            .tv_sec = 0,
            .tv_nsec = microseconds * 1000,
        },
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

void my_timerfd_start_interval_ns(my_timerfd_t fd_timer, time_t nanoseconds)
{
    assert(nanoseconds < 1000 * 1000 * 1000);   // TODO verify
    struct itimerspec timerspec = {
        .it_value = {0},
        .it_interval = {
            .tv_sec = 0,
            .tv_nsec = nanoseconds,
        },
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

void my_timerfd_set(my_timerfd_t fd_timer,
    int flags,
    const struct itimerspec *new_timer,
    struct itimerspec *old_timer)
{
    int err = timerfd_settime(fd_timer.fd, flags, new_timer, old_timer);
    assert(!err);
}

void my_timerfd_remaining(my_timerfd_t fd_timer, struct itimerspec *timerspec)
{
    int err = timerfd_gettime(fd_timer.fd, timerspec);
    assert(!err);
}

void my_timerfd_stop(my_timerfd_t fd_timer)
{
    struct itimerspec timerspec = {
        .it_value = {
            .tv_sec = 0,
            .tv_nsec = 0,
        }
        // Clearing the interval value is unnecessary
    };
    my_timerfd_set(fd_timer, 0, &timerspec, NULL);
}

uint64_t my_timerfd_read(my_timerfd_t fd_timer)
{
    uint64_t n_timeouts = 0;
    int err = read(fd_timer.fd, &n_timeouts, sizeof(n_timeouts));
    assert(err == sizeof(uint64_t));
    return n_timeouts;
}

void my_timerfd_clear_event(my_timerfd_t fd_timer)
{
    my_timerfd_read(fd_timer);
}

bool my_timerfd_is_armed(my_timerfd_t fd_timer)
{
    struct itimerspec timerspec = {0};
    int err = timerfd_gettime(fd_timer.fd, &timerspec);
    assert(!err);

    // The interval value is ignored in this context
    if (timerspec.it_value.tv_sec != 0)
    {
        return true;
    }
    if (timerspec.it_value.tv_nsec != 0)
    {
        return true;
    }
    return false;
}

bool my_timerfd_is_oneshot(my_timerfd_t fd_timer)
{
    struct itimerspec timerspec = {0};
    int err = timerfd_gettime(fd_timer.fd, &timerspec);
    assert(!err);

    // Assuming that the timer is armed!
    if (timerspec.it_interval.tv_sec != 0)
    {
        return false;
    }
    if (timerspec.it_interval.tv_nsec != 0)
    {
        return false;
    }
    return true;
}
