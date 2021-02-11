/**
 * @file my_signal.h
 * @{
 */
#ifndef MY_SIGNAL_H_INCLUDED
#define MY_SIGNAL_H_INCLUDED

#include <signal.h>

enum my_signal_sigmask_flags_t
{
    MY_SIGNAL_SIGMASK_FLAG_BLOCK = SIG_BLOCK,
    MY_SIGNAL_SIGMASK_FLAG_UNBLOCK = SIG_UNBLOCK,
    MY_SIGNAL_SIGMASK_FLAG_SET = SIG_SETMASK,
};

// TODO add SA_NODEFER, SA_ONSTACK, etc
enum my_signal_sigaction_flags_t
{
    MY_SIGNAL_SIGACTION_FLAG_NONE = 0,
    MY_SIGNAL_SIGACTION_FLAG_ONESHOT = SA_RESETHAND,
};

typedef void (* my_signal_handler_t)(int signal_num);

/**
 * @brief Remove add signals from a signal set.
 */
void my_signal_empty_set(sigset_t* signal_set) __nonnull();

/**
 * @brief Add all signals to a signal set.
 */
void my_signal_fill_set(sigset_t* signal_set) __nonnull();

/**
 * @brief Add one signal to a set.
 *
 * Possible signals are defined in signum-generic.h.
 * @param signal_set
 * @param signal_num
 */
void my_signal_add_to_set(sigset_t* signal_set, int signal_num) __nonnull();

/**
 * @brief Block until one signal occurs.
 *
 * @param signal_set
 * @return The signal that occurred.
 */
int my_signal_wait(sigset_t* signal_set) __nonnull();

/**
 * @brief Helper function to wait for a specific signal
 */
void my_signal_wait_signal(int signal_num);

/**
 * @brief Change the signal mask of a "process".
 *
 * @warning
 * This function is not thread-safe!
 * Behavior in a multi-threaded environment is unspecified.
 *
 * @param signal_set
 * @param how
 */
void my_signal_change_process_sigmask(sigset_t* signal_set,
    enum my_signal_sigmask_flags_t how) __nonnull();

/**
 * @brief Change the signal mask of the current thread.
 *
 * @param signal_set
 * @param how
 */
void my_signal_change_thread_sigmask(sigset_t* signal_set,
    enum my_signal_sigmask_flags_t how) __nonnull();

/**
 * @brief Helper function to block a signal set.
 * @param signal_set
 */
void my_signal_block_sigset(sigset_t* signal_set);

/**
 * @brief Helper function to unblock a signal set.
 * @param signal_set
 */
void my_signal_unblock_sigset(sigset_t* signal_set);

/**
 * @brief Helper function to block a specific signal.
 * @param signal_num
 */
void my_signal_block_signo(int signal_num);

/**
 * @brief Helper function to unblock a specific signal.
 * @param signal_num
 */
void my_signal_unblock_signo(int signal_num);

// TODO use signal()
// TODO This is deprecated, right?
// void my_signal_set_signal_handler(void);

//TODO does __nonnull() work for function pointers?
// TODO can the signal mask can be null?
// The signal mask prevents other signals from occurring while the signal handler is executing.
// The signal that triggered the handler is blocked by default.
void my_signal_set_sigaction(int signal_num,
    my_signal_handler_t signal_handler,
    sigset_t* signal_mask,
    enum my_signal_sigaction_flags_t flags) __nonnull((2));

void my_signal_set_sigaction2(int signal_num, my_signal_handler_t signal_handler) __nonnull();

void my_signal_set_sigaction_oneshot(int signal_num,
    my_signal_handler_t signal_handler) __nonnull();

#endif

/** @} */
