#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>

#include "hash_map.h"

int main(int argc, char const *argv[])
{
    HashMap map = new_HashMap();
    char input_buffer[32];
    int value;
    scanf("%31s", input_buffer);
    while (!ferror(stdin) && !feof(stdin))
    {
        // Exit sentinel values
        if (!strcmp("exit", input_buffer) || !strcmp("quit", input_buffer))
            break;
        // Put
        else if (!strcmp("put", input_buffer))
        {
            // Make sure there is another value
            if (scanf("%31s %d", input_buffer, &value))
                put_map(&map, input_buffer, value);
            else
                printf("Incorrect number of arguments\n");
        }
        // Get
        else if (!strcmp("get", input_buffer))
        {
            // Make sure there is another value
            if (scanf("%31s", input_buffer))
                printf("%s -> %d\n", input_buffer, get_map(&map, input_buffer));
            else
                printf("Incorrect number of arguments\n");
        }
        // Unknown
        else
            printf("Unknown command '%.31s'\n", input_buffer);

        scanf("%31s", input_buffer);
    }
    if (feof(stdin))
        printf("stdin error\n");

    delete_HashMap(&map);
    return 0;
}
