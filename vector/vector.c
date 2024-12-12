#include <stdio.h>
#include <errno.h>
#include <limits.h>

#include "vector_template.h"

DEF_VEC(int)

int main(int argc, char const *argv[])
{
    int_Vec vec = new_int_Vec();
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

        append_int_Vec(&vec, (int)value);
    }

    for (size_t i = 0; i < vec.len; i++)
        printf("%d ", vec.arr[i]);
    printf("\n");
CLEANUP:
    free(vec.arr);
    return 0;
}
