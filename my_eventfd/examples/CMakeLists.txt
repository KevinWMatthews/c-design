add_executable(eventfd_blocking eventfd_blocking.c)

add_executable(eventfd_blocking_multi eventfd_blocking_multi.c)
target_link_libraries(eventfd_blocking_multi
    PRIVATE
    Threads::Threads
    )

add_executable(eventfd_nonblocking eventfd_nonblocking.c)
