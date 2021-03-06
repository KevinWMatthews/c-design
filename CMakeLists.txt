# May work with earlier versions but only tested with this
cmake_minimum_required(VERSION 3.16)

project(design VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

option(OPTIMIZE "Set a custom optimization value" OFF)
include(GccOptions)
include(GccCustomTargets)
include(CompilationDatabase)
include(Cppcheck)
include(Unity)

add_subdirectory(asan)
add_subdirectory(atomics)
add_subdirectory(epoll)
add_subdirectory(event_loop)
add_subdirectory(eventfd)
add_subdirectory(hash_tables/intro)
add_subdirectory(hsearch)
add_subdirectory(pthread)
add_subdirectory(shared_state)
add_subdirectory(signal)
add_subdirectory(signalfd)
add_subdirectory(timerfd)
add_subdirectory(tsan)
add_subdirectory(ubsan)
