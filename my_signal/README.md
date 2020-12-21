# Signals

TODO Revise this.

## Background

By default, signals are asynchronously delivered to a process.
The action on delivery is determined by a process's "disposition", which is one of:

  * default - `Term`, `Ign`, `Core`, `Stop`, `Cont`
  * ignore - do nothing
  * execute a caller-provided function pointer (a signal handler)

The disposition can be configured per signal using `sigaction()` (recommended) or `signal()` (not recommended).

While the disposition of a signal can be changed, the default action itself can not be altered (as far as I know).
For example,

  * `SIGINT` -> `Term`
  * `SIGABRT` -> `Core`
  * `SIGSTP` -> `Stop`
  * `SIGCHLD` -> `Ign`

In addition to the process-wide signal disposition, each thread within a process has a "signal mask".
Signals that are added to the mask (blocked) will not be delivered.
Instead, the incoming signal is marked as pending.

Pending signals are delivered when:

  * a thread explicitly consumes the signal
  * the signal is removed from the signal mask

If a signal is removed from the signal mask (unblocked),
the signal is delivered asynchronously and the process behaves according to that signal's disposition.

Alternatively, a signal can be consumed synchronously using:

  * sigwait(), sigtimedwait(), siginfo()
  * a signalfd() and read()


## TODO

TODO what if not all threads block a signal?
Does the process disposition or the waiting thread catch the signal?

TODO add explicit section about sync vs async delivery.
async signals interrupt system calls, etc.

TODO add section about calls that return `EINTR` in Linux but not in `POSIX`, such as `epoll_wait()`.

POSIX specifies that blocking system calls will return `EINTR` if a signal handler is executed.
However, POSIX implies that signals with a default disposition of `Stop` should not interrupt blocking system calls.

They note that Linux deviates from this, specifically that `Stop` and `SIGCONT` will cause system calls to
return an "unsanctioned" `EINTR`. This has a real-world impact;
gdb can not place breakpoints while a process is running (?),
so debuggers must stop and resume a process to place breakpoints at runtime.
This can cause unexpected failure from system calls such as `epoll_wait()`.

See

    Interruption of system calls and library functions by signal handlers

and

    Interruption of system calls and library functions by stop signals

within
[signal(7)](https://man7.org/linux/man-pages/man7/signal.7.html)

## TODO

  * Extract details from the code and put them here, or maybe move everything to the README
  * Add bad example of not blocking signals. Random thread receives signal?

Signal *disposition* is a per-process attribute.
It can be changed using `sigaction()`.

Signal *mask* is a per-thread attribute.
It can be changed with `sigprocmask()` or `pthread_sigmask()` for single or multi threaded applications, respectively.

From [the docs](https://man7.org/linux/man-pages/man7/signal.7.html):

Signal disposition:

    The signal disposition is a per-process attribute: in a multithreaded
    application, the disposition of a particular signal is the same for
    all threads.

Signal mask:

    Each thread in a process has an independent signal mask, which
    indicates the set of signals that the thread is currently blocking.
    A thread can manipulate its signal mask using pthread_sigmask(3).  In
    a traditional single-threaded application, sigprocmask(2) can be used
    to manipulate the signal mask.


Signal handlers are set by changing the signal disposition.
These signal handlers are asynchronous to the *process*.
The interrupt everything; signal-safety is very stringent.

If the signal disposition is changed to ignore the signal (the signal is blocked),
then the signal will not be delivered (pending) until the application requests it.
This allows signals that are generated asynchronously to be delivered synchronously.
This could occur:

  * never
  * `sitwait()` or its relatives
  * `signalfd()`, with either blocking or non-blocking read

Synchronous signal delivery is possible *only* if the signal is blocked.
If the signal disposition is not changed, then the process will simply be terminated.
