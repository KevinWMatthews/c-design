include(CheckIncludeFile)
CHECK_INCLUDE_FILE("sys/timerfd.h" HAVE_SYS_TIMERFD_H)
if(NOT HAVE_SYS_TIMERFD_H)
    message(FATAL_ERROR "Could not find system header file: <sys/timerfd.h>")
endif()

add_library(my_timerfd
    src/my_timerfd.c
    )
target_include_directories(my_timerfd
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
add_library(my_timerfd::my_timerfd ALIAS my_timerfd)

add_subdirectory(examples)
