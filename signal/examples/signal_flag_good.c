/**
 * @file signal_flag_good.c
 *
 * Signal handler that sets a volatile flag.
 * This is in accordance with the C11 spec.
 *
 * WARNING: the thread sanitizer interferes with signal delivery!
 * "Generally tsan delivers signals only at designated points, which are some/most syscalls and atomic operations.
 * If code loops in an infinite loop, it may never receive the signal."
 * https://github.com/google/sanitizers/issues/1179
 */
#include <signal.h>
#include <assert.h>
#include <stdio.h>

volatile sig_atomic_t flag;

void sigint_handler(int signo)
{
    // Print statements are not signal safe!
    flag = 1;
}

int main(void)
{
    printf("Starting...\n");
    int err;

    printf("Setting SIGINT handler\n");
    int flags = 0;

    sigset_t sigset = {0};
    err = sigemptyset(&sigset);
    assert(!err);

    const struct sigaction action = {
        .sa_handler = sigint_handler,
        // Block these signals while the signal handler callback is executing.
        // The signal that triggered the handler is blocked by default.
        .sa_mask = sigset,
        .sa_flags = flags,
    };
    int signo = SIGINT;
    struct sigaction old_action = {0};
    err = sigaction(signo, &action, &old_action);
    assert(!err);

    printf("Waiting for SIGINT...\n");
    while (1)
    {
        if (flag)
        {
            printf("Main loop detected flag\n");
            break;
        }
    }

    printf("Done\n");
    return 0;
}
