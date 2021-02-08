include(CheckIncludeFile)
check_include_file("sys/signalfd.h" HAVE_SYS_SIGNALFD_H)
if(NOT HAVE_SYS_SIGNALFD_H)
    message(FATAL_ERROR "Could not find system header file: <sys/signalfd.h>")
endif()
check_include_file("signal.h" HAVE_SIGNAL_H)
if(NOT HAVE_SIGNAL_H)
    message(FATAL_ERROR "Could not find system header file: <signal.h>")
endif()

add_subdirectory(examples)