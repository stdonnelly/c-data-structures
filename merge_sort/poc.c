// Proof of concept of merge sort
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "merge_sort.h"

// Allows testing of merge sort header
int main(int argc, char const *argv[])
{
    // Read arguments at integers
    int *arr = malloc(sizeof(int) * (argc - 1));
    for (int i = 1; i < argc; i++)
    {
        long value = strtol(argv[i], NULL, 10);
        if (errno)
        {
            perror("Error reading argument");
            goto CLEANUP;
        }
        else if (value < INT_MIN)
        {
            fprintf(stderr, "Value %ld is too low to represent as an integer\n", value);
            goto CLEANUP;
        }
        else if (value > INT_MAX)
        {
            fprintf(stderr, "Value %ld is too high to represent as an integer\n", value);
            goto CLEANUP;
        }

        arr[i - 1] = (int)value;
    }

    // Sort and print
    merge_sort(arr, argc - 1);
    for (int i = 0; i < argc - 1; i++)
        printf("%d ", arr[i]);
    printf("\n");

CLEANUP:
    free(arr);
    return 0;
}
