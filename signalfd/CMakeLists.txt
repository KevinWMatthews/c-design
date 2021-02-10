include(CheckIncludeFile)

check_include_file("sys/signalfd.h" HAVE_SYS_SIGNALFD_H)
if(NOT HAVE_SYS_SIGNALFD_H)
    message(FATAL_ERROR "Could not find system header file: <sys/signalfd.h>")
endif()

check_include_file("signal.h" HAVE_SIGNAL_H)
if(NOT HAVE_SIGNAL_H)
    message(FATAL_ERROR "Could not find system header file: <signal.h>")
endif()

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

add_library(my_signalfd src/my_signalfd.c)
target_include_directories(my_signalfd
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
target_link_libraries(my_signalfd
    PRIVATE
    # pthread is required to set the sigmask in a multi threaded application
    my_signal::my_signal
    Threads::Threads
    )
# TODO install public header file
add_library(my_signalfd::my_signalfd ALIAS my_signalfd)

add_subdirectory(examples)
