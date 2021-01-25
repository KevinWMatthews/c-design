set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

add_library(my_pthread
    src/my_pthread.c
    )
target_include_directories(my_pthread
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
target_link_libraries(my_pthread
    PUBLIC
    Threads::Threads
    )
add_library(my_pthread::my_pthread ALIAS my_pthread)

add_subdirectory(examples)
