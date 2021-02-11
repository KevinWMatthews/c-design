/**
 * @file signalfd_wait_multi_bad.c
 * Wait for a signal at the application level using signalfd.
 * The application is multi-threaded.
 *
 * @warning
 * This example illustrates problematic behavior!
 * The parent thread sets the signal mask *after* spawning,
 * so the spawned thread inherits a signal mask with SIGINT unblocked.
 * The spawned thread does not block SIGINT, so the kernel will deliver
 * SIGINT to it and execute SIGINT's default disposition: Term.
 *
 * @warning
 * The behavior of this program is inconsistent!
 * Both threads wait for SIGINT, and the kernel can deliver the signal to the thread of its choice.
 * This behavior may be infrequent but I have observed it repeatedly.
 */
#include <sys/signalfd.h>
#include <signal.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

/**
 * Block SIGINT in the spawned thread.
 * If defined, both threads can receive SIGINT at the application level.
 * If undefined, the spawned thread's default SIGINT disposition terminates the application.
 */
#define SPAWNED_BLOCK_SIGINT

static void* thread_function(void* unused);

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

    /*
     * Spawn child thread
     * This thread inherits the current signal mask.
     */
    pthread_t thread_handle;
    err = pthread_create(&thread_handle, NULL, thread_function, NULL);
    assert(!err);

    err = pthread_detach(thread_handle);
    assert(!err);

    /*
     * Block SIGINT
     * This prevents the signal's default disposition (Term) from executing
     */
    int how;
    sigset_t old_sigset = {0};
    printf("Main thread blocking SIGINT\n");
    how = SIG_BLOCK;
    err = pthread_sigmask(how, &sigset, &old_sigset);
    assert(!err);

    /*
     * Wait for SIGINT (blocking read)
     */
    printf("Main thread waiting for SIGINT...\n");
    struct signalfd_siginfo siginfo = {0};     // Can be an array
    ssize_t buffer_size = sizeof(siginfo);
    ssize_t bytes_read = read(sfd, &siginfo, buffer_size);
    assert(bytes_read == buffer_size);

    /*
     * Unblock SIGINT
     * This allows a second SIGINT to execute the default disposition and terminate the application
     */
    how = SIG_UNBLOCK;
    err = sigprocmask(how, &sigset, &old_sigset);
    assert(!err);
    printf("SIGINT Unblocked\n");

    int actual_signo = siginfo.ssi_signo;
    assert(actual_signo == signo);
    printf("Main thread received signal: %d\n", actual_signo);

    /*
     * Teardown
     */
    err = close(sfd);
    assert(!err);

    printf("Main thread done\n");
    return 0;
}

static void* thread_function(void* unused)
{
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

#ifdef SPAWNED_BLOCK_SIGINT
    printf("Spawned thread blocking SIGINT\n");
    int how;
    sigset_t old_sigset = {0};
    how = SIG_BLOCK;
    err = pthread_sigmask(how, &sigset, &old_sigset);
    assert(!err);
#endif

    printf("Spawned thread waiting for SIGINT...\n");
    struct signalfd_siginfo siginfo = {0};     // Can be an array
    ssize_t buffer_size = sizeof(siginfo);
    ssize_t bytes_read = read(sfd, &siginfo, buffer_size);
    assert(bytes_read == buffer_size);

    printf("Spawned thread received signal: %d\n", siginfo.ssi_signo);

    err = close(sfd);
    assert(!err);

    printf("Spawned thread done\n");
    return NULL;
}
