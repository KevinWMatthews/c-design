/**
 * @file my_timerfd.h
 * @{
 */
#ifndef MY_TIMERFD_H_INCLUDED
#define MY_TIMERFD_H_INCLUDED

#include <sys/timerfd.h>
#include <inttypes.h>
#include <stdbool.h>

typedef struct my_timerfd_s
{
    int fd;
} my_timerfd_t;

enum my_timerfd_flags_t
{
    MY_TIMERFD_FLAGS_BLOCKING = 0,
    MY_TIMERFD_FLAGS_NONBLOCKING = TFD_NONBLOCK,
};

// TODO expose different clock types
// TODO make CLOEXEC an option
my_timerfd_t my_timerfd_open(enum my_timerfd_flags_t flags);
void my_timerfd_close(my_timerfd_t fd_timer);

// Setting to 0 disarms the timer!
// milli/micro/nanosecond values must not be greater than 1 second?
void my_timerfd_start_oneshot_s(my_timerfd_t fd_timer, time_t seconds);
void my_timerfd_start_oneshot_ms(my_timerfd_t fd_timer, time_t milliseconds);
void my_timerfd_start_oneshot_us(my_timerfd_t fd_timer, time_t microseconds);
void my_timerfd_start_oneshot_ns(my_timerfd_t fd_timer, time_t nanoseconds);
void my_timerfd_start_interval_s(my_timerfd_t fd_timer, time_t seconds);
void my_timerfd_start_interval_ms(my_timerfd_t fd_timer, time_t milliseconds);
void my_timerfd_start_interval_us(my_timerfd_t fd_timer, time_t microseconds);
void my_timerfd_start_interval_ns(my_timerfd_t fd_timer, time_t nanoseconds);

void my_timerfd_remaining(my_timerfd_t fd_timer, struct itimerspec *timerspec);

void my_timerfd_stop(my_timerfd_t fd_timer);

// Returns the number of timeouts
uint64_t my_timerfd_read(my_timerfd_t fd_timer);
void my_timerfd_clear_event(my_timerfd_t fd_timer);

bool my_timerfd_is_armed(my_timerfd_t fd_timer);
bool my_timerfd_is_oneshot(my_timerfd_t fd_timer);

// Possible flags:
// TFD_TIMER_ABSTIME
// TFD_TIMER_CANCEL_ON_SET
void my_timerfd_set(my_timerfd_t fd_timer,
    int flags,
    const struct itimerspec *new_timer,
    struct itimerspec *old_timer);

#endif

/** @} */
