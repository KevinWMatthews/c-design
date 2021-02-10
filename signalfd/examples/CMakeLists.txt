add_executable(signalfd_wait_single signalfd_wait_single.c)

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

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
