/**
 * @file my_signal_wait2.c
 * Wait for multiple signals in a single-threaded application.
 */
#include "my_signal.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Starting...\n");

    sigset_t signal_set = {0};
    my_signal_empty_set(&signal_set);
    my_signal_add_to_set(&signal_set, SIGINT);
    my_signal_add_to_set(&signal_set, SIGTERM);

    my_signal_change_thread_sigmask(&signal_set, MY_SIGNAL_SIGMASK_FLAG_BLOCK);

    printf("Waiting for SIGINT/SIGTERM...\n");
    int signal = my_signal_wait(&signal_set);

    my_signal_change_thread_sigmask(&signal_set, MY_SIGNAL_SIGMASK_FLAG_UNBLOCK);
    printf("Received signal: '%d'\n", signal);

    //*
    printf("Application is hanging (terminate with SIGINT/SIGTERM)...\n");
    while (1)
    {
        sleep(1);     // Block, allowing the user to terminate with a second SIGINT
    }
    // */

    printf("Done\n");
}
