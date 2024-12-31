// Proof of concept for hash_map library
#include <stdio.h>
#include <string.h>

#include "hash_map.h"

int main(int argc, char const *argv[])
{
    HashMap map = new_HashMap();
    char input_buffer[32];
    long long value;
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
            if (scanf("%31s %lld", input_buffer, &value))
                put_map(&map, input_buffer, (union Value){.val = value});
            else
                printf("Incorrect number of arguments\n");
        }
        // Get
        else if (!strcmp("get", input_buffer))
        {
            // Make sure there is another value
            if (scanf("%31s", input_buffer))
            {
                if (get_map(&map, input_buffer, &(union Value){.val = value}))
                    printf("%s -> %lld\n", input_buffer, value);
                else
                    printf("%s -> None\n", input_buffer);
            }
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
