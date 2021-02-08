/**
 * @file my_timerfd.h
 * @{
 */
#ifndef MY_TIMERFD_H_INCLUDED
#define MY_TIMERFD_H_INCLUDED

#include <sys/timerfd.h>
#include <inttypes.h>
#include <stdbool.h>

/**
 * @brief Encapsulate a timerfd's file descriptor to provide type safety.
 *
 * If direct access to the bare file descriptor is required, simply access the struct member.
 */
typedef struct my_timerfd_s
{
    int fd;
} my_timerfd_t;

/**
 * @brief List of valid flags for creating a timerfd.
 * @note TIMER_CLOEXEC is automatically appended to these flags!
 * @todo Make CLOEXEC an option
 */
enum my_timerfd_flags_t
{
    MY_TIMERFD_FLAGS_BLOCKING = 0,
    MY_TIMERFD_FLAGS_NONBLOCKING = TFD_NONBLOCK,
};

/**
 * @brief Create and open a timerfd file descriptor.
 *
 * TODO expose different clock types
 *
 * @param flags
 * @return A valid timerfd.
 */
my_timerfd_t my_timerfd_open(enum my_timerfd_flags_t flags);

/**
 * @brief Close a timerfd.
 * @param fd_timer
 */
void my_timerfd_close(my_timerfd_t fd_timer);

// TODO test
void my_timerfd_start_oneshot(my_timerfd_t fd_timer, time_t seconds, time_t nanoseconds);
void my_timerfd_start_oneshot_s(my_timerfd_t fd_timer, time_t seconds);
void my_timerfd_start_oneshot_ms(my_timerfd_t fd_timer, time_t milliseconds);
void my_timerfd_start_oneshot_us(my_timerfd_t fd_timer, time_t microseconds);
void my_timerfd_start_oneshot_ns(my_timerfd_t fd_timer, time_t nanoseconds);

// TODO test
void my_timerfd_start_interval(my_timerfd_t fd_timer, time_t seconds, time_t nanoseconds);
void my_timerfd_start_interval_s(my_timerfd_t fd_timer, time_t seconds);
void my_timerfd_start_interval_ms(my_timerfd_t fd_timer, time_t milliseconds);
void my_timerfd_start_interval_us(my_timerfd_t fd_timer, time_t microseconds);
void my_timerfd_start_interval_ns(my_timerfd_t fd_timer, time_t nanoseconds);

// TODO test
void my_timerfd_start(my_timerfd_t fd_timer, time_t initial_seconds, time_t initial_nanoseconds,
    time_t repeat_seconds, time_t repeat_nanoseconds);

/**
 * @brief Stop the timer.
 *
 * Sets the current timer value to 0.
 *
 * @param fd_timer
 */
void my_timerfd_stop(my_timerfd_t fd_timer);

/**
 * @brief Return the amount of time remaining in the current cycle.
 *
 * If both fields are zero, the timer is not running.
 * Valid for both one-shot and interval timers.
 *
 * @param fd_timer
 * The timer to query.
 * @return A struct containing the timer settings.
 * Returned by copy.
 */
struct timespec my_timerfd_remaining(my_timerfd_t fd_timer);

/**
 * @brief Return the interval settings for the timer.
 *
 * If a one-shot timer, both fields are zero.
 *
 * @param fd_timer
 * The timer to query.
 * @return A struct containing the timer settings.
 * Returned by copy.
 */
struct timespec my_timerfd_interval_settings(my_timerfd_t fd_timer);

/**
 * @brief Read the timerfd's value: the number of timeouts that have occurred since the last read.
 *
 * If the timer has expired at least once, always returns immediately.
 * If the timer is blocking and the timer has not expired, the read will block.
 * If the timer is non-blocking and the timer has not expired, returns 0.
 *
 * @return The number of timeouts since the last read.
 */
uint64_t my_timerfd_read(my_timerfd_t fd_timer);

/**
 * @brief Clear any pending file reads on the timer.
 *
 * Designed for use with non-blocking timers where the number of timeouts is not a concern.
 * Read from a file that has been marked as ready and discard the read result.
 *
 * @warning Not for use with blocking timers! This could cause a timer to block.
 *
 * @param fd_timer
 */
void my_timerfd_clear_event(my_timerfd_t fd_timer);

/**
 * @brief Query if the timer is running.
 * @param fd_timer
 * @return
 */
bool my_timerfd_is_armed(my_timerfd_t fd_timer);

/**
 * @brief Query if the timer is one-shot.
 *
 * True only if the interval timer settings are cleared.
 * TODO check if the timer is running?
 *
 * @param fd_timer
 * @return
 */
bool my_timerfd_is_oneshot(my_timerfd_t fd_timer);

/**
 * @brief Thin wrapper over the timer set system call.
 *
 * The API is identical to timerfd_settime().
 *
 * @param fd_timer
 * @param flags
 * @param new_timer
 * @param old_timer
 */
void my_timerfd_set(my_timerfd_t fd_timer,
    int flags,
    const struct itimerspec* new_timer,
    struct itimerspec* old_timer) __nonnull((3));

/**
 * @brief Thin wrapper over the timer get system call.
 *
 *  The API is identical to timerfd_gettime().
 *
 * @param fd_timer
 * @param current
 */
void my_timerfd_get(my_timerfd_t fd_timer, struct itimerspec* current) __nonnull((2));

#endif

/** @} */
