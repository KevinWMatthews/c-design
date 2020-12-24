/**
 * @file my_pthread.h
 * TODO Rethink the naming convention.
 * TODO Write down design principles: no return codes so can return values
 * @{
 */
#ifndef MY_PTHREAD_H_INCLUDED
#define MY_PTHREAD_H_INCLUDED

#include <pthread.h>

typedef void *(*my_pthread_start_routine_t )(void *);

pthread_t my_pthread_create(my_pthread_start_routine_t start_routine,
    void *arg,
    const pthread_attr_t *attr);
pthread_t my_pthread_create_noattr(my_pthread_start_routine_t start_routine, void *arg);
pthread_t my_pthread_create_noarg(my_pthread_start_routine_t start_routine);

void *my_pthread_join(pthread_t handle);
void my_pthread_join_noarg(pthread_t handle);

#endif

/** @} */
