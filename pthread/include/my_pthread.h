/**
 * @file my_pthread.h
 * TODO Rethink the naming convention.
 * TODO Write down design principles: no return codes so can return values
 * @{
 */
#ifndef MY_PTHREAD_H_INCLUDED
#define MY_PTHREAD_H_INCLUDED

#include <pthread.h>

/**
 * @brief Prototype for a pthread function.
 */
typedef void* (* my_pthread_start_routine_t)(void*);

/**
 * @brief Create a thread.
 *
 * The resulting thread must be either joined or detached.
 *
 * @param start_routine
 * @param arg
 * @param attr
 * @return
 */
pthread_t my_pthread_create(my_pthread_start_routine_t start_routine,
    const pthread_attr_t* attr,
    void* arg);

/**
 * @brief Create a thread with default attributes.
 *
 * The resulting thread must be either joined or detached.
 *
 * @param start_routine
 * @param arg
 * @return
 */
pthread_t my_pthread_create_noattr(my_pthread_start_routine_t start_routine, void* arg);

/**
 * @brief Create a thread with default attributes and no arguments.
 *
 * The resulting thread must be either joined or detached.
 *
 * @param start_routine
 * @return
 */
pthread_t my_pthread_create_noarg(my_pthread_start_routine_t start_routine);

/**
 * @brief Create and detach a thread.
 * @param start_routine
 * @param arg
 * @param attr
 */
void my_pthread_spawn(my_pthread_start_routine_t start_routine,
    const pthread_attr_t* attr,
    void* arg);

/**
 * @brief Create and detach a thread with default attributes and no arguments.
 * @param start_routine
 * @param arg
 */
void my_pthread_spawn_noattr(my_pthread_start_routine_t start_routine, void* arg);

/**
 * @brief Create and detach a thread with default attributes and no arguments.
 * @param start_routine
 */
void my_pthread_spawn_noarg(my_pthread_start_routine_t start_routine);

/**
 * @brief Detach a thread.
 */
void my_pthread_detach(pthread_t handle);

/**
 * @brief Join a thread and return the thread's return value.
 * @param handle
 * @return
 */
void* my_pthread_join(pthread_t handle);

/**
 * @brief Join a thread and ignore the thread's return value.
 * @param handle
 */
void my_pthread_join_noarg(pthread_t handle);

#endif

/** @} */
