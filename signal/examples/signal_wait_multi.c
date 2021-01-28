/**
 * @file signal_wait_multi.c
 * Wait for a signal at the application level, multi-threaded.
 * This requires changing the signal's disposition - blocking the signal.
 *
 *TODO implement.
 * Demonstrate:
 * - sigprocmask() is not thread safe
 * - child threads inherit parent thread's sigmask
 * - signal is delivered to a single thread (technically the OS's choice)
 */
#include "signal_wait_multi.h"
