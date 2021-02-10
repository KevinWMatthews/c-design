/**
 * @file my_signalfd.c
 */
#include "my_signalfd.h"
#include "my_signal.h"
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

my_signalfd_t my_signalfd_open(sigset_t* sigset, enum my_signalfd_flags_t flags)
{
    assert(sigset);
    flags |= SFD_CLOEXEC;
    // Pass -1 to return a new file descriptor
    // Pass an existing file descriptor and it will be replaced
    int fd = signalfd(-1, sigset, flags);
    assert(fd != -1);
    my_signalfd_t my_signalfd = {
        .fd = fd,
    };
    return my_signalfd;
}

my_signalfd_t my_signalfd_open_single(int signo, enum my_signalfd_flags_t flags)
{
    sigset_t sigset = {0};
    my_signal_empty_set(&sigset);
    my_signal_add_to_set(&sigset, signo);

    flags |= SFD_CLOEXEC;
    // Pass -1 to return a new file descriptor
    // Pass an existing file descriptor and it will be replaced
    int fd = signalfd(-1, &sigset, flags);
    assert(fd != -1);
    my_signalfd_t my_signalfd = {
        .fd = fd,
    };
    return my_signalfd;
}

void my_signalfd_close(my_signalfd_t fd_signal)
{
    int err = close(fd_signal.fd);
    assert(!err);
}

size_t my_signalfd_read(my_signalfd_t fd_signal,
    struct signalfd_siginfo* signal_list,
    size_t signal_list_len)
{
    assert(signal_list);
    size_t max_bytes = sizeof(*signal_list) * signal_list_len;
    ssize_t bytes_read = read(fd_signal.fd, signal_list, max_bytes);
    if (bytes_read == -1)
    {
        assert(errno == EAGAIN);
    }
    // TODO can n_read == 0 be indicative of an error?
    // TODO verify this
    return bytes_read / sizeof(*signal_list);
}

int my_signalfd_read_single(my_signalfd_t fd_signal)
{
    struct signalfd_siginfo signal_info = {0};
    size_t signal_info_len = sizeof(signal_info);
    size_t signals_read = my_signalfd_read(fd_signal, &signal_info, signal_info_len);
    assert(signals_read == 1 || signals_read == 0);
    return signal_info.ssi_signo;
}

void my_signalfd_clear_event(my_signalfd_t fd_signal, size_t signal_list_len)
{
    // TODO Rethink and test this algorithm!
    struct signalfd_siginfo* signal_list = calloc(signal_list_len, sizeof(*signal_list));
    assert(signal_list);
    size_t signals_read = 0;
    do
    {
        signals_read = my_signalfd_read(fd_signal, signal_list, signal_list_len);
    } while (signals_read);
}
