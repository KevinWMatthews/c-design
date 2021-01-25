/**
 * @file leak.c
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    printf("Leak some memory?\n");
    // Dynamically allocate memory
    char *string1 = strdup("This is a string");

    // Use the memory to produce a side effect so the optimizer can't remove the memory allocation
    printf("%s\n", string1);

    // Clean up the memory (or not)
    /*
    free(string1);
    // */

    // The address sanitizer will not report a leak unless the program exits gracefully
    /*
    abort();
    // */

    // If the program exits success and there is a leak,
    // asan will override the application's return code with its own and report memory leaks
    /*
    exit(EXIT_SUCCESS);
    // */

    // If the program exits failure and there is a leak,
    // asan will override the application's return code with its own and report memory leaks
    //*
    exit(-42);
    // */
}
