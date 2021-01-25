/**
 * @file my_pthread.c
 */
#include <assert.h>
#include "my_pthread.h"

pthread_t my_pthread_create(my_pthread_start_routine_t start_routine,
    void *arg,
    const pthread_attr_t *attr)
{
    pthread_t handle;
    int err = pthread_create(&handle, attr, start_routine, arg);
    assert(!err);
    return handle;
}

pthread_t my_pthread_create_noattr(my_pthread_start_routine_t start_routine, void *arg)
{
    pthread_t handle;
    int err = pthread_create(&handle, NULL, start_routine, arg);
    assert(!err);
    return handle;
}

pthread_t my_pthread_create_noarg(my_pthread_start_routine_t start_routine)
{
    pthread_t handle;
    int err = pthread_create(&handle, NULL, start_routine, NULL);
    assert(!err);
    return handle;
}

void *my_pthread_join(pthread_t handle)
{
    void *retval = NULL;
    int err = pthread_join(handle, &retval);
    assert(!err);
    return retval;
}

void my_pthread_join_noarg(pthread_t handle)
{
    int err = pthread_join(handle, NULL);
    assert(!err);
}
