# Atomics

Too hard. Don't use atomics if at all possible.

## TODO

`atomic_store()`/`atomic_store_explicit()`:

* Which is correct?
  - CLion raises a warning when `obj` is type `atomic_bool` but not when it is `bool`
  - Sourcetrail raises a warning when `obj` is a `bool` but not an `atomic_bool`.
  - I think this is a bug in CLion
    + https://youtrack.jetbrains.com/issue/CPP-14801
    + https://youtrack.jetbrains.com/issue/CPP-15688
    + https://youtrack.jetbrains.com/issue/CPP-1164
* Do atomic types need to be explicitly marked as `volatile`?

## Links

* [Atomic’s memory orders, what for? - Frank Birbacher (ACCU 2017)](https://www.youtube.com/watch?v=A_vAG6LIHwQ)
* [CppCon 2019: Rainer Grimm “Atomics, Locks, and Tasks (part 1 of 2)”](https://www.youtube.com/watch?v=o0i2fc0Keo8)
* [CppCon 2017: Fedor Pikus “C++ atomics, from basic to advanced. What do they really do?”](https://www.youtube.com/watch?v=ZQFzMfHIxng)
* [Deprecating volatile - JF Bastien - CppCon 2019](https://www.youtube.com/watch?v=KJW_DLaVXIY)
* [CppCon 2016: JF Bastien “No Sane Compiler Would Optimize Atomics"](https://www.youtube.com/watch?v=IB57wIf9W1k)
* [CppCon 2017: Fedor Pikus “Read, Copy, Update, then what? RCU for non-kernel programmers”](https://www.youtube.com/watch?v=rxQ5K9lo034)
* [Linux-Kernel Memory Ordering: Help Arrives At Last!](https://www.youtube.com/watch?v=ULFytshTvIY)
* [From Weak to Weedy: Effective Use of Memory Barriers in the ARM Linux Kernel - W. Deacon, ARM](https://www.youtube.com/watch?v=6ORn6_35kKo)
* [Computer Architecture - Lecture 21b: Memory Ordering (Memory Consistency) (ETH Zürich, Fall 2019)](https://www.youtube.com/watch?v=VP-5fizCUbw)
* [Understanding the C runtime memory model](https://www.youtube.com/watch?v=3F3lp_F2YpQ)
* [Arvid Norberg: The C++ memory model: an intuition](https://www.youtube.com/watch?v=OyNG4qiWnmU)
* [A Relaxed Guide to memory_order_relaxed - Paul E. McKenney & Hans Boehm - CppCon 2020](https://www.youtube.com/watch?v=OyNG4qiWnmU)
