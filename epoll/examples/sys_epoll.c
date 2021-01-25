/**
 * @file sys_epoll.c
 * Match file descriptors
 */
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include <sys/signalfd.h>
#include <signal.h>
#include <assert.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define EVENT_LIST_LEN      10
#define SIGNAL_LIST_LEN     10

void process_timer_event(int fd);
void process_signal_event(int fd);

int main(void)
{
    int err;
    int epfd = epoll_create1(EPOLL_CLOEXEC);
    assert(epfd != -1);

    sigset_t sigmask = {0};
    err = sigemptyset(&sigmask);
    assert(!err);
    err = sigaddset(&sigmask, SIGINT);
    assert(!err);
    err = sigaddset(&sigmask, SIGTERM);
    assert(!err);
    int sfd = -1;
    sfd = signalfd(sfd, &sigmask, SFD_CLOEXEC | SFD_NONBLOCK);
    assert(sfd != -1);

    struct epoll_event sfd_event = {
        .events = EPOLLIN,
        .data.fd = sfd,     // <-- Data passed to epoll event
    };
    err = epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &sfd_event);
    assert(!err);

    int tfd = timerfd_create(CLOCK_REALTIME, TFD_CLOEXEC | TFD_NONBLOCK);
    assert(tfd != -1);

    struct epoll_event tfd_event = {
        .events = EPOLLIN,
        .data.fd = tfd,     // <-- Data passed to epoll event
    };
    err = epoll_ctl(epfd, EPOLL_CTL_ADD, tfd, &tfd_event);
    assert(!err);

    struct itimerspec timer_spec = {
        .it_value.tv_sec = 2,
        .it_interval.tv_sec = 2,
    };
    err = timerfd_settime(tfd, 0, &timer_spec, NULL);
    assert(!err);

    err = pthread_sigmask(SIG_BLOCK, &sigmask, NULL);
    assert(!err);

    struct epoll_event event_list[EVENT_LIST_LEN] = {0};
    size_t event_list_len = sizeof(event_list) / sizeof(*event_list);
    // -1 == no timeout
    // 0 == timeout immediately
    int timeout_ms = 1000;
    while (1)
    {
        int n_events = epoll_wait(epfd, event_list, event_list_len, timeout_ms);
        if (n_events == -1)
        {
            if (errno == EINTR)
            {
                // epoll() returns failure if interrupted by a signal
                // gdb can't place breakpoints at runtime,
                // so debuggers typically send SIGSTOP
                continue;
            }
        }
        assert(n_events != -1);

        if (n_events == 0 && timeout_ms > 0)
        {
            printf("Epoll timeout occurred\n");
            continue;
        }
        for (int i = 0; i < n_events; i++)
        {
            struct epoll_event *this_event = &event_list[i];
            // Must read the file descriptor to clear the epoll event!
            // If not read,
            // - level triggered events will reoccur immediately
            // - edge triggered events will never occur again
            int fd = this_event->data.fd;   // <-- Data extracted from epoll event
            if (fd == tfd)
            {
                printf("Timer event\n");
                process_timer_event(tfd);
            }
            else if (fd == sfd)
            {
                printf("Signal event\n");
                process_signal_event(sfd);
                // Break out of nested loops
                goto shutdown;
            }
        }
    }

shutdown:
    err = pthread_sigmask(SIG_UNBLOCK, &sigmask, NULL);
    assert(!err);

    // Not necessary since the tfd and the epoll fd will be closed
    err = epoll_ctl(epfd, EPOLL_CTL_DEL, tfd, NULL);
    assert(!err);

    err = epoll_ctl(epfd, EPOLL_CTL_DEL, sfd, NULL);
    assert(!err);

    err = close(tfd);
    assert(!err);

    err = close(sfd);
    assert(!err);

    err = close(epfd);
    assert(!err);
    return 0;
}

void process_timer_event(int fd)
{
    uint64_t value = 0;
    size_t buffer_size = sizeof(value);
    ssize_t result = read(fd, &value, buffer_size);
    assert(result != -1);
    assert(result == buffer_size);
    printf("Timer timeouts: %" PRIu64 "\n", value);
}

void process_signal_event(int fd)
{
    struct signalfd_siginfo list[SIGNAL_LIST_LEN] = {0};
    size_t buffer_size = sizeof(list);
    ssize_t bytes_read = read(fd, &list, buffer_size);
    assert(bytes_read != -1);
    assert(bytes_read > 0);

    //TODO what is the termination condition for a loop? The length of the list? ssi_signo == 0?
    size_t n_signals = bytes_read / sizeof(*list);
    for (int i = 0; i < n_signals; ++i)
    {
        int signo = list[i].ssi_signo;
        if (signo == 0)
        {
            break;
        }
        printf("Signal received: %d\n", signo);
    }
}
