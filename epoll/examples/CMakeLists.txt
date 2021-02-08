add_executable(my_epoll_empty my_epoll_empty.c)
target_link_libraries(my_epoll_empty PRIVATE my_epoll::my_epoll)

add_executable(my_epoll_event_empty my_epoll_event_empty.c)
target_link_libraries(my_epoll_event_empty PRIVATE my_epoll::my_epoll)

add_executable(my_epoll_event_intro my_epoll_event_intro.c)
target_link_libraries(my_epoll_event_intro
    PRIVATE
    my_epoll::my_epoll
    # TODO
#    my_signalfd::my_signalfd
    my_timerfd::my_timerfd
    )

add_executable(sys_epoll_empty sys_epoll_empty.c)

add_executable(sys_epoll sys_epoll.c)
target_link_libraries(sys_epoll PRIVATE Threads::Threads)
