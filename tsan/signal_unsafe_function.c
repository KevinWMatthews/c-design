/**
 * @file signal_unsafe_function.c
 * Call a signal-unsafe function within a signal handler.
 */
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_signal.h"

void signal_handler(int signal_num)
{
    printf("Signal unsafe function call\n");

    // The thread sanitizer only reports signal-unsafe calls on shutdown.
    // exit() is not required to be signal safe; _exit()/_Exit() are.
    _Exit(EXIT_SUCCESS);
}

int main(void)
{
    my_signal_set_sigaction_oneshot(SIGINT, signal_handler);

    // If printf() is called before the signal handler is executed, then
    // the thread sanitizer doesn't report an error when printf() is called in the signal handler.
    // printf()'s underlying call to malloc() raise an error, and this seems to be conditional.
    /*
    printf("Waiting for SIGINT...\n");
    // */

    while (1)
    {
        sleep(1);
    }

    return 0;
}
