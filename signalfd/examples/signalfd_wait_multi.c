/**
 * @file signalfd_wait_multi.c
 * Wait for a signal at the application level using signalfd.
 * The application is multi-threaded.
 * This example uses a blocking read, but this can be combined with epoll using a non-blocking
 * file descriptor (or by waiting on both file events and signals).
 *
 * @warning
 * The behavior of this program is inconsistent!
 * Both threads wait for SIGINT, and the kernel can deliver the signal to the thread of its choice.
 * This behavior may be infrequent but I have observed it repeatedly.
 */
#include <sys/signalfd.h>
#include <signal.h>
// signal.h includes <bits/sigthread.h>, which declares pthread_sigmask()
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <stdio.h>

static void* thread_function(void* unused);

int main(void)
{
    printf("Starting...\n");
    int err;

    /*
     * Create signalfd
     */
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
     * Block SIGINT
     * This prevents the signal's default disposition (Term) from executing
     *
     * Block signals *before* spawning threads
     * Threads inherit the signal mask of their parent
     */
    int how;
    sigset_t old_sigset = {0};
    printf("Main thread blocking SIGINT\n");
    how = SIG_BLOCK;
    err = pthread_sigmask(how, &sigset, &old_sigset);
    assert(!err);

    /*
     * Spawn child thread
     */
    pthread_t thread_handle;
    err = pthread_create(&thread_handle, NULL, thread_function, NULL);
    assert(!err);

    err = pthread_detach(thread_handle);
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
    printf("Main thread unblocked SIGINT\n");

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

    printf("Spawned thread waiting for SIGINT...\n");
    struct signalfd_siginfo siginfo = {0};     // Can be an array
    ssize_t buffer_size = sizeof(siginfo);
    ssize_t bytes_read = read(sfd, &siginfo, buffer_size);
    assert(bytes_read == buffer_size);

    int actual_signal = siginfo.ssi_signo;
    assert(actual_signal == signo);
    printf("Spawned thread received signal: %d\n", actual_signal);

    err = close(sfd);
    assert(!err);

    printf("Spawned thread done\n");
    return NULL;
}
