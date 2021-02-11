/**
 * @file my_pthread.c
 */
#include <assert.h>
#include "my_pthread.h"

pthread_t my_pthread_create(my_pthread_start_routine_t start_routine,
    const pthread_attr_t* attr,
    void* arg)
{
    pthread_t handle;
    int err = pthread_create(&handle, attr, start_routine, arg);
    assert(!err);
    return handle;
}

pthread_t my_pthread_create_noattr(my_pthread_start_routine_t start_routine, void* arg)
{
    return my_pthread_create(start_routine, NULL, arg);
}

pthread_t my_pthread_create_noarg(my_pthread_start_routine_t start_routine)
{
    return my_pthread_create(start_routine, NULL, NULL);
}

void my_pthread_spawn(my_pthread_start_routine_t start_routine,
    const pthread_attr_t* attr,
    void* arg)
{
    pthread_t handle = my_pthread_create(start_routine, attr, arg);
    pthread_detach(handle);
}

void my_pthread_spawn_noattr(my_pthread_start_routine_t start_routine, void* arg)
{
    my_pthread_spawn(start_routine, NULL, arg);
}

void my_pthread_spawn_noarg(my_pthread_start_routine_t start_routine)
{
    my_pthread_spawn(start_routine, NULL, NULL);
}

void my_pthread_detach(pthread_t handle)
{
    int err = pthread_detach(handle);
    assert(!err);
}

void* my_pthread_join(pthread_t handle)
{
    void* retval = NULL;
    int err = pthread_join(handle, &retval);
    assert(!err);
    return retval;
}

void my_pthread_join_noarg(pthread_t handle)
{
    my_pthread_join(handle);
}
