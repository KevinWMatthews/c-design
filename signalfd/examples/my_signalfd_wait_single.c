/**
 * @file my_signalfd_wait_single.c
 * Wait for a signal in a single-threaded application.
 * Waiting for a one occurrence of this signal.
 */
#include "my_signalfd.h"
#include "my_signal.h"
#include <stdio.h>
#include <unistd.h>
#include <assert.h>

#define BLOCK_SIGINT
#define UNBLOCK_SIGINT
// #define HANG_ON_EXIT

int main(void)
{
    printf("Starting...\n");

    enum my_signalfd_flags_t flags = MY_SIGNALFD_FLAG_BLOCKING;
    my_signalfd_t fd_signal = my_signalfd_open_signo(SIGINT, flags);

    int signo = SIGINT;
#ifdef BLOCK_SIGINT
    printf("Blocking SIGINT\n");
    my_signal_block_signo(signo);
#endif

    printf("Waiting for SIGINT...\n");
    int actual_signo = my_signalfd_read_signo(fd_signal);
    assert(actual_signo == signo);

#ifdef UNBLOCK_SIGINT
    my_signal_unblock_signo(signo);
    printf("Unblocked SIGINT\n");
#endif

    printf("Received signal: %d\n", actual_signo);

    my_signalfd_close(fd_signal);

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
