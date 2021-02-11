/**
 * @file my_signal_wait.c
 * Wait for one signal in a single-threaded application.
 */
#include "my_signal.h"
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("Starting...\n");
    // If SIGINT is not blocked, then the process executes SIGINTs default disposition: Term
    // The application terminates immediately.
    my_signal_block_signo(SIGINT);

    printf("Waiting for SIGINT...\n");
    my_signal_wait_signal(SIGINT);

    // If SIGINT is not unblocked, then all further SIGINTs are effectively ignored.
    // They are queued for processing by the application.
    // Unblock as quickly as possible.
    my_signal_unblock_signo(SIGINT);
    printf("Received SIGINT\n");

    //*
    printf("Application is hanging (terminate with SIGINT)...\n");
    while (1)
    {
        sleep(1);     // Block, allowing the user to terminate with a second SIGINT
    }
    // */

    printf("Done\n");
}
