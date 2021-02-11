/**
 * @file my_signal.c
 */
#include <assert.h>
#include <stddef.h>
#include "my_signal.h"

void my_signal_empty_set(sigset_t* signal_set)
{
    assert(signal_set);
    int err = sigemptyset(signal_set);
    assert(!err);
}

void my_signal_fill_set(sigset_t* signal_set)
{
    assert(signal_set);
    int err = sigfillset(signal_set);
    assert(!err);
}

void my_signal_add_to_set(sigset_t* signal_set, int signal_num)
{
    assert(signal_set);
    int err = sigaddset(signal_set, signal_num);
    assert(!err);
}

int my_signal_wait(sigset_t* signal_set)
{
    assert(signal_set);
    int actual_signal_num;
    int err = sigwait(signal_set, &actual_signal_num);
    assert(!err);
    return actual_signal_num;
}

void my_signal_wait_signal(int signal_num)
{
    sigset_t signal_set = {0};
    my_signal_empty_set(&signal_set);
    my_signal_add_to_set(&signal_set, signal_num);
    int actual_signal_num = my_signal_wait(&signal_set);
    assert(signal_num == actual_signal_num);
}

void my_signal_change_process_sigmask(sigset_t* signal_set, enum my_signal_sigmask_flags_t how)
{
    assert(signal_set);
    sigset_t* old_signal_set = NULL;
    int err = sigprocmask(how, signal_set, old_signal_set);
    assert(!err);
}

void my_signal_change_thread_sigmask(sigset_t* signal_set, enum my_signal_sigmask_flags_t how)
{
    assert(signal_set);
    sigset_t* old_signal_set = NULL;
    // In a multi threaded application:
    // - sigprocmask() is unspecified
    // - pthread_sigmask() is thread-safe
    int err = pthread_sigmask(how, signal_set, old_signal_set);
    assert(!err);
}

void my_signal_block_sigset(sigset_t* signal_set)
{
    my_signal_change_thread_sigmask(signal_set, SIG_BLOCK);
}

void my_signal_unblock_sigset(sigset_t* signal_set)
{
    my_signal_change_thread_sigmask(signal_set, SIG_UNBLOCK);
}

void my_signal_block_signo(int signal_num)
{
    sigset_t signal_set = {0};
    my_signal_empty_set(&signal_set);
    my_signal_add_to_set(&signal_set, signal_num);
    my_signal_change_thread_sigmask(&signal_set, MY_SIGNAL_SIGMASK_FLAG_BLOCK);
}

void my_signal_unblock_signo(int signal_num)
{
    sigset_t signal_set = {0};
    my_signal_empty_set(&signal_set);
    my_signal_add_to_set(&signal_set, signal_num);
    my_signal_change_thread_sigmask(&signal_set, MY_SIGNAL_SIGMASK_FLAG_UNBLOCK);
}

void my_signal_set_sigaction(int signal_num,
    my_signal_handler_t signal_handler,
    sigset_t* signal_mask,
    enum my_signal_sigaction_flags_t flags)
{
    // sa_mask may be null?
    const struct sigaction action = {
        .sa_handler = signal_handler,
        .sa_mask = *signal_mask,    // TODO does this work as expected? No!
        .sa_flags = flags,
    };
    struct sigaction old_signal_action = {0};
    int err = sigaction(signal_num, &action, &old_signal_action);
    assert(!err);
}

void my_signal_set_sigaction2(int signal_num, my_signal_handler_t signal_handler)
{
    sigset_t signal_mask = {0};
    my_signal_empty_set(&signal_mask);
    my_signal_set_sigaction(signal_num, signal_handler, &signal_mask,
        MY_SIGNAL_SIGACTION_FLAG_NONE);
}

void my_signal_set_sigaction_oneshot(int signal_num, my_signal_handler_t signal_handler)
{
    sigset_t signal_mask = {0};
    my_signal_empty_set(&signal_mask);
    my_signal_set_sigaction(signal_num, signal_handler, &signal_mask,
        MY_SIGNAL_SIGACTION_FLAG_ONESHOT);
}
