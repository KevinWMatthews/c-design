include(CheckIncludeFile)
check_include_file("signal.h" HAVE_SIGNAL_H)
if(NOT HAVE_SIGNAL_H)
    message(FATAL_ERROR "Could not find system header file: <signal.h>")
endif()

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

add_library(my_signal
    src/my_signal.c
    )
target_include_directories(my_signal
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
target_link_libraries(my_signal
    PRIVATE
    # pthread is required to set the sigmask in a multi threaded application
    Threads::Threads
    )
add_library(my_signal::my_signal ALIAS my_signal)
# TODO install public header file

add_subdirectory(examples)
