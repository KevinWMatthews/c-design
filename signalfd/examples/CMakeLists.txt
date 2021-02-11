add_executable(signalfd_wait_single signalfd_wait_single.c)

add_executable(signalfd_wait_multi signalfd_wait_multi.c)
target_link_libraries(signalfd_wait_multi
    PRIVATE
    Threads::Threads
    )

add_executable(signalfd_wait_multi_bad signalfd_wait_multi_bad.c)
target_link_libraries(signalfd_wait_multi_bad
    PRIVATE
    Threads::Threads
    )

add_executable(my_signalfd_wait my_signalfd_wait.c)
target_link_libraries(my_signalfd_wait
    PRIVATE
    my_signalfd::my_signalfd
    my_signal::my_signal
    )

add_executable(my_signalfd_wait_single my_signalfd_wait_single.c)
target_link_libraries(my_signalfd_wait_single
    PRIVATE
    my_signalfd::my_signalfd
    my_signal::my_signal
    )

add_executable(my_signalfd_wait_multi my_signalfd_wait_multi.c)
target_link_libraries(my_signalfd_wait_multi
    PRIVATE
    my_signalfd::my_signalfd
    my_signal::my_signal
    my_pthread::my_pthread
    )
