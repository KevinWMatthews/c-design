/**
 * @file signal_wait_single.c
 *
 * Wait for a signal at the application level, single-threaded.
 * This requires changing the signal's disposition - blocking the signal.
 *
 * If a signal is not blocked, the default disposition executes.
 * For SIGINT, this is Term; the program executes immediately.
 * If a signal remains blocked, the default disposition never executes.
 * For SIGINT, blocking permanently can cause the program to "hang".
 *
 * Changes the signal disposition using a thread-safe pthread function, pthread_sigmask().
 * The POSIX function sigprocmask() is not thread-safe.
 */
#include <signal.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

/**
 * If signal is not blocked, default disposition executes.
 * If signal is not unblocked, signals are queued for the application.
 * This is most noticeable if the program hangs; the default disposition does not execute.
 */
#define BLOCK_SIGINT
#define UNBLOCK_SIGINT
// #define HANG_ON_EXIT

int main(void)
{
    printf("Starting...\n");
    int err;

    sigset_t sigset = {0};
    err = sigemptyset(&sigset);
    assert(!err);

    int signo = SIGINT;
    err = sigaddset(&sigset, signo);
    assert(!err);

    int how;
    sigset_t old_sigset = {0};
#ifdef BLOCK_SIGINT
    // Block SIGINT
    // This prevents the signal's default disposition (Term) from executing
    printf("Blocking SIGINT\n");
    how = SIG_BLOCK;
    // WARNING: not thread safe! For multi-threaded programs, use pthread_sigmask()
    err = sigprocmask(how, &sigset, &old_sigset);
    assert(!err);
#endif

    printf("Waiting for SIGINT...\n");
    int actual_signo = 0;
    // Alternately, use sigwaitinfo()
    err = sigwait(&sigset, &actual_signo);
    assert(!err);

#ifdef UNBLOCK_SIGINT
    how = SIG_UNBLOCK;
    err = pthread_sigmask(SIG_UNBLOCK, &sigset, &old_sigset);
    assert(!err);
    printf("SIGINT Unblocked\n");
#endif

    printf("Received signal: %d\n", actual_signo);

#ifdef HANG_ON_EXIT
    printf("Hanging...\n");
    while (1)
    {
        sleep(1);
    }
#endif

    printf("Done\n");
    return 0;
}
