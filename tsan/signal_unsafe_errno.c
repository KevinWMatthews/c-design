/**
 * @file signal_unsafe_errno.c
 * Modify/spoil errno within a signal handler.
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include "my_signal.h"

static sig_atomic_t volatile terminate_flag;

void signal_handler(int signal_num)
{
    int tmp = errno;

    // The thread sanitizer will report if errno is "spoiled"
    errno = 1;

    // errno can modified if it is saved and restored
    // https://man7.org/linux/man-pages/man7/signal-safety.7.html
    // TODO check the assembly to see if errno is volatile or if access is optimized away
#if 0
    errno = tmp;
#else
    (void)tmp;
#endif

    // If the program is exited during a signal handler, then
    // the thread sanitizer will not detect that errno is spoiled.
    /*
    _exit(0);
    // */

    terminate_flag = 1;
}

int main(void)
{
    my_signal_set_sigaction_oneshot(SIGINT, signal_handler);

    printf("Waiting for SIGINT...\n");
    while (1)
    {
        if (terminate_flag)
        {
            break;
        }
        sleep(1);
    }

    printf("Done\n");
    return 0;
}
