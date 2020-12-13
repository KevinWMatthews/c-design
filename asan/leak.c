/**
 * @file leak.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    printf("Leak some memory?\n");
    char *string1 = strdup("This is a string");
    printf("%s\n", string1);
    /*
    free(string1);
    // */

    // The address sanitizer will not report a leak unless the program exits gracefully
    /*
    abort();
    // */

    // If the program exits success and there is a leak, asan will override the return code
    //*
    exit(EXIT_SUCCESS);
    // */

    // If the program exits failure and there is a leak, asan reports the return code
    /*
    exit(EXIT_FAILURE);
    // */
}
