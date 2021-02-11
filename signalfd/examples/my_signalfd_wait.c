/**
 * @file my_signalfd_wait.c
 */
#include "my_signalfd.h"
#include "my_signal.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(void)
{
    printf("Starting...\n");

    enum my_signalfd_flags_t flags = MY_SIGNALFD_FLAG_BLOCKING;
    sigset_t sigset = {0};
    my_signal_empty_set(&sigset);
    my_signal_add_to_set(&sigset, SIGINT);
    my_signal_add_to_set(&sigset, SIGTERM);
    my_signal_add_to_set(&sigset, SIGUSR1);
    my_signal_add_to_set(&sigset, SIGUSR2);
    my_signalfd_t fd_signal = my_signalfd_open_sigset(&sigset, flags);

    printf("Blocking signals...\n");
    my_signal_block_sigset(&sigset);

    printf("Waiting for signals...\n");
    while (1)
    {
        struct signalfd_siginfo signal_list[2] = {0};
        size_t signal_list_len = sizeof(signal_list) / sizeof(*signal_list);
        size_t n_signals = my_signalfd_read_sigset(fd_signal, signal_list, signal_list_len);
        for (size_t i = 0; i < n_signals; i++)
        {
            int actual_signo = signal_list[i].ssi_signo;
            if (actual_signo == SIGINT)
            {
                my_signal_unblock_signo(SIGINT);
            }

            printf("Received signal: %d\n", actual_signo);
            if (actual_signo == SIGTERM)
            {
                exit(EXIT_SUCCESS);
            }
            else if (actual_signo == SIGINT)
            {
                goto shutdown;
            }
            else
            {
                // Put other handling routines here
                continue;
            }
        }
    }

shutdown:
    printf("Shutting down...\n");
    my_signalfd_close(fd_signal);
    printf("Done\n");
    return 0;
}
