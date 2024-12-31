#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "hash_map.h"

static int should_grow_HashMap(HashMap *map);
static void grow_HashMap(HashMap *map);
static uint32_t crc32(const char *input);

HashMap new_HashMap()
{
    HashMap map;
    // Defaults from Java standard libray
    map.capacity = 4;
    map.load_factor = 0.75;
    map.buckets = calloc(map.capacity, sizeof(map.buckets[0]));
    map.size = 0;
    return map;
}

void delete_HashMap(HashMap *map)
{
    for (int i = 0; i < map->capacity; i++)
    {
        MapEntry *bucket_node = map->buckets[i];
        while (bucket_node)
        {
            MapEntry *next = bucket_node->next;
            free(bucket_node->key);
            free(bucket_node);
            bucket_node = next;
        }
    }
    free(map->buckets);
}

int get_map(HashMap *map, char *key)
{
    int value = -1;
    // Get CRC32 hash and apply bit mask
    unsigned long hash = crc32(key);
    hash &= map->capacity - 1;

    MapEntry *entry = map->buckets[hash];
    while (entry)
    {
        // If the key is equal, use this value
        if (!strcmp(entry->key, key))
        {
            value = entry->value;
            break;
        }

        // If not equal, try the next value in this bucket
        entry = entry->next;
    }

    return value;
}

void put_map(HashMap *map, char *key, int value)
{
    // printf("Putting value '%d' at key '%s' in map...\n", value, key);
    // Add an element to the size and check if this should grow
    map->size++;
    if (should_grow_HashMap(map))
        grow_HashMap(map);

    // Get CRC32 hash and apply bit mask
    int key_length = strlen(key);
    unsigned long hash = crc32(key);
    hash &= map->capacity - 1;

    // Pointer to the bucket pointer so we can modify the bucket pointer instead of just the bucket
    MapEntry **bucket = &(map->buckets[hash]);
    while (*bucket)
    {
        // Check if the key is equal
        if (!strcmp((*bucket)->key, key))
        {
            // If the key matches, replace the value
            (*bucket)->value = value;
            // And note that nothing was actually added
            map->size--;
            return;
        }
        // Next bucket
        bucket = &((*bucket)->next);
    }

    // If we got to the end of the while loop without finding the key, add a new one
    *bucket = malloc(sizeof(**bucket));
    (*bucket)->next = NULL;
    (*bucket)->key = malloc(key_length + 1);
    memcpy((*bucket)->key, key, key_length + 1);
    (*bucket)->value = value;
}

// Static function

/// @brief Check if a hashmap should grow
/// @param map The map
/// @return 1 if this should grow, 0 if this should not grow
static int should_grow_HashMap(HashMap *map)
{
    return ((double)(map->capacity) * map->load_factor) < (double)(map->size);
}

// Grow the capacity of the map
static void grow_HashMap(HashMap *map)
{
    // Get old capacity and double it
    int old_cap = map->capacity;
    map->capacity = old_cap << 1;
    map->size = 0;

    // Pointer to the old array
    MapEntry **old_table = map->buckets;

    // Resize the array
    map->buckets = calloc(map->capacity, sizeof(map->buckets[0]));

    // Loop over all elements in the old table
    for (int i = 0; i < old_cap; i++)
    {
        // Loop over all elements in the bucket
        MapEntry *bucket = old_table[i];
        while (bucket)
        {
            // Put this into the new map
            put_map(map, bucket->key, bucket->value);

            // Get the next element and free this one
            MapEntry *next = bucket->next;
            free(bucket->key);
            free(bucket);
            bucket = next;
        }
    }

    // Finally, free the old table
    free(old_table);
}

static uint32_t crc32(const char *input)
{
    // The result, start with 0
    // This is 64-bit because we need bit 32 to determine if we should XOR the polynomial
    uint64_t result = 0;
    // Polynomial for the standard CRC-32
    const uint32_t polynomial = 0x04C11DB7;

    while (*input)
    {
        // Look over bits in input, starting with the most significant
        for (int i = 7; i >= 0; i--)
        {
            // Shift result
            result <<= 1;
            // Shift in input
            result |= (*input >> i) & 1;

            // Do crc calculation
            // Check bit 32
            if (result & ((uint64_t)1 << 32))
                // If this matches, do the XOR
                result ^= polynomial;
        }
        // Next character
        input++;
    }

    // Do the last 32 bits
    for (int i = 0; i < 32; i++)
    {
        result <<= 1;
        // Do crc calculation
        // Check bit 32
        if (result & ((uint64_t)1 << 32))
            // If this matches, do the XOR
            result ^= polynomial;
    }

    // Invert the result before returning
    return ~(uint32_t)result;
}
