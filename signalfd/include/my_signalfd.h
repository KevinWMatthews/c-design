/**
 * @file my_signalfd.h
 * This wrapper around Linux' signalfd API.
 * TODO test this!
 * @{
 */
#ifndef MY_SIGNALFD_H_INCLUDED
#define MY_SIGNALFD_H_INCLUDED

#include <sys/signalfd.h>
#include <stddef.h>

// CLOEXEC is appended internally
enum my_signalfd_flags_t
{
    MY_SIGNALFD_FLAG_BLOCKING = 0,
    MY_SIGNALFD_FLAG_NONBLOCKING = SFD_NONBLOCK,
};

typedef struct my_signalfd_s
{
    int fd;
} my_signalfd_t;

/**
 * @brief Open a signalfd with a user-defined signal set.
 * @param signo
 * @param flags
 * @return
 */
my_signalfd_t my_signalfd_open_sigset(sigset_t* sigset, enum my_signalfd_flags_t flags);

/**
 * @brief Open a signalfd that can receive a single signal.
 * @param signo
 * @param flags
 * @return
 */
my_signalfd_t my_signalfd_open_signo(int signo, enum my_signalfd_flags_t flags);

/**
 * @brief Close a signalfd.
 */
void my_signalfd_close(my_signalfd_t);

/**
 * @brief Read signals into a list.
 * @return The number of signals that were read (not the number of bytes that were read!).
 */
size_t my_signalfd_read_sigset(my_signalfd_t fd_signal,
    struct signalfd_siginfo* signal_list,
    size_t signal_list_len);

/**
 * @brief Read a single signal.
 * @param fd_signal
 * @return The signal number.
 */
int my_signalfd_read_signo(my_signalfd_t fd_signal);

/**
 * @brief Clear any pending file reads on the signalfd.
 *
 * Read from a file that has been marked as ready and discard the read result.
 * Designed for use with non-blocking signalfds where the number of signals
 * and the signal itself are not a concern.
 *
 * @warning Not for use with blocking signalfds! This could cause the read to block.
 *
 * @param fd_signal
 */
// TODO do we want this?
void my_signalfd_clear_events(my_signalfd_t fd_signal, size_t signal_list_len);

#endif

/** @} */
