add_executable(eventfd_blocking eventfd_blocking.c)

add_executable(eventfd_blocking_multi eventfd_blocking_multi.c)
target_link_libraries(eventfd_blocking_multi
    PRIVATE
    Threads::Threads
    )

add_executable(eventfd_nonblocking eventfd_nonblocking.c)

add_executable(my_eventfd_blocking my_eventfd_blocking.c)
target_link_libraries(my_eventfd_blocking
    PRIVATE
    my_eventfd::my_eventfd
    )

add_executable(my_eventfd_blocking_multi my_eventfd_blocking_multi.c)
target_link_libraries(my_eventfd_blocking_multi
    PRIVATE
    my_eventfd::my_eventfd
    Threads::Threads
    )

add_executable(my_eventfd_nonblocking my_eventfd_nonblocking.c)
target_link_libraries(my_eventfd_nonblocking
    PRIVATE
    my_eventfd::my_eventfd
    )
