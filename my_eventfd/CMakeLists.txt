include(CheckIncludeFile)
CHECK_INCLUDE_FILE("sys/eventfd.h" HAVE_SYS_EVENTFD_H)
if(NOT HAVE_SYS_EVENTFD_H)
    message(FATAL_ERROR "Could not find system header file: <sys/eventfd.h>")
endif()

add_library(my_eventfd
    src/my_eventfd.c
    src/my_eventfd_sem.c
    )
target_include_directories(my_eventfd
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )
add_library(my_eventfd::my_eventfd ALIAS my_eventfd)

add_subdirectory(examples)
