include(CheckIncludeFile)
CHECK_INCLUDE_FILE("signal.h" HAVE_SIGNAL_H)
if(NOT HAVE_SIGNAL_H)
    message(FATAL_ERROR "Could not find system header file: <signal.h>")
endif()

set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads)

add_executable(sigmask_single_thread examples/sigmask_single_thread.c)
target_link_libraries(sigmask_single_thread PRIVATE Threads::Threads)

add_executable(signal_flag_bad examples/signal_flag_bad.c)
target_link_libraries(signal_flag_bad PRIVATE Threads::Threads)
create_custom_gcc_targets(TARGET_NAME signal_flag_bad)

add_executable(signal_flag_good examples/signal_flag_good.c)
target_link_libraries(signal_flag_good PRIVATE Threads::Threads)
create_custom_gcc_targets(TARGET_NAME signal_flag_good)
