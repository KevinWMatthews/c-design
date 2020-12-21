add_library(my_epoll
    src/my_epoll.c
    src/my_epoll_event.c
    )
target_include_directories(my_epoll
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
add_library(my_epoll::my_epoll ALIAS my_epoll)
