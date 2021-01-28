/**
 * @file signalfd_wait.c
 * Wait for a signal at the application level using signalfd.
 * This example uses a blocking read, but this can be combined with epoll using a non-blocking
 * file descriptor (or by waiting on both file events and signals).
 */
#include <sys/signalfd.h>
#include <signal.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

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

    int flags = SFD_CLOEXEC;
    int sfd = -1;   // Set to -1 to create a new signalfd
    sfd = signalfd(sfd, &sigset, flags);
    assert(sfd != -1);

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
    struct signalfd_siginfo siginfo = {0};     // Can be an array
    ssize_t buffer_size = sizeof(siginfo);
    ssize_t bytes_read = read(sfd, &siginfo, buffer_size);
    assert(bytes_read == buffer_size);

#ifdef UNBLOCK_SIGINT
    how = SIG_UNBLOCK;
    err = sigprocmask(how, &sigset, &old_sigset);
    assert(!err);
    printf("SIGINT Unblocked\n");
#endif

    printf("Received signal: %d\n", siginfo.ssi_signo);

    err = close(sfd);
    assert(!err);

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
