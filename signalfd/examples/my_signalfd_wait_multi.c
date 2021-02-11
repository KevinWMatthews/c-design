/**
 * @file my_signalfd_wait_multi.c
 */
#include "my_signalfd.h"
#include "my_signal.h"
#include "my_pthread.h"
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

static void* thread_function(void* unused);

int main(void)
{
    printf("Starting...\n");

    /*
     * Create signalfd
     */
    int signo = SIGINT;
    enum my_signalfd_flags_t flags = MY_SIGNALFD_FLAG_BLOCKING;
    my_signalfd_t fd_signal = my_signalfd_open_single(signo, flags);

    /*
     * Block SIGINT
     * This prevents the signal's default disposition (Term) from executing
     *
     * Block signals *before* spawning threads
     * Threads inherit the signal mask of their parent
     */
    my_signal_block_signal(signo);

    /*
     * Spawn child thread
     */
    my_pthread_spawn_noarg(thread_function);

    /*
     * Wait for SIGINT (blocking read)
     */
    printf("Main thread waiting for SIGINT...\n");
    int actual_signo = my_signalfd_read_single(fd_signal);
    assert(actual_signo == signo);

    /*
     * Unblock SIGINT
     * This allows a second SIGINT to execute the default disposition and terminate the application
     */
    my_signal_unblock_signal(signo);

    printf("Main thread received signal: %d\n", actual_signo);

    /*
     * Teardown
     */
    my_signalfd_close(fd_signal);
    printf("Main thread done\n");
    return 0;
}

static void* thread_function(void* unused)
{
    printf("Spawned thread starting...\n");
    int signo = SIGINT;
    enum my_signalfd_flags_t flags = MY_SIGNALFD_FLAG_BLOCKING;
    my_signalfd_t fd_signal = my_signalfd_open_single(signo, flags);

    printf("Spawned thread waiting for SIGINT...\n");
    int actual_signo = my_signalfd_read_single(fd_signal);
    assert(actual_signo == signo);

    printf("Spawned thread received signal: %d\n", actual_signo);

    my_signalfd_close(fd_signal);

    printf("Spawned thread done\n");
    return NULL;
}
