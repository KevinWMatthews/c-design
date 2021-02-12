#include <stdio.h>

static int function(int *arg)
{
    return *arg;
}

int main(void)
{
    int value = 42;
    value = function(&value);
    printf("%d\n", value);

    //*
    value = function(NULL);
    printf("%d\n", value);
    // */

    return 0;
}
