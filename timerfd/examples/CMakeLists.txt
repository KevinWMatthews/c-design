add_executable(timerfd_blocking timerfd_blocking.c)

add_executable(my_timerfd_oneshot my_timerfd_oneshot.c)
target_link_libraries(my_timerfd_oneshot PRIVATE my_timerfd::my_timerfd)

add_executable(my_timerfd_interval my_timerfd_interval.c)
target_link_libraries(my_timerfd_interval PRIVATE my_timerfd::my_timerfd)

add_executable(my_timerfd_read my_timerfd_read.c)
target_link_libraries(my_timerfd_read PRIVATE my_timerfd::my_timerfd)

add_executable(my_timerfd_remaining my_timerfd_remaining.c)
target_link_libraries(my_timerfd_remaining PRIVATE my_timerfd::my_timerfd)
