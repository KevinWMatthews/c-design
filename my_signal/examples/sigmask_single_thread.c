/**
 * @file sigmask_single_thread.c
 *
 * Example of signal disposition using SIGINT.
 * If a signal is not blocked, the default disposition executes.
 * For SIGINT, this is Term; the program executes immediately.
 * If a signal remains blocked, the default disposition never executes.
 * For SIGINT, blocking permanently can cause the program to "hang".
 */
#include <signal.h>
#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

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
    // TODO there are details here - why is pthread preferred?
    // Block SIGINT
    // This prevents the signal's default disposition (Term) from executing
#ifdef BLOCK_SIGINT
    printf("Blocking SIGINT\n");
    how = SIG_BLOCK;
    sigset_t *old_sigset = NULL;
    err = pthread_sigmask(how, &sigset, old_sigset);
    assert(!err);
#endif

    printf("Waiting for SIGINT...\n");
    int actual_signo = 0;
    err = sigwait(&sigset, &actual_signo);
    assert(!err);

#ifdef UNBLOCK_SIGINT
    how = SIG_UNBLOCK;
    err = pthread_sigmask(SIG_UNBLOCK, &sigset, old_sigset);
    assert(!err);
    printf("SIGINT Unblocked\n");
#endif

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
