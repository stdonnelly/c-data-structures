#pragma once

/// @brief Entry in a HashMap
typedef struct MapEntry
{
    struct MapEntry *next;
    char *key;
    int value;
} MapEntry;

/// @brief Instance of a hashmap
typedef struct HashMap
{
    // An array of buckets, which are themselves represented as singly-linked list nodes
    MapEntry **buckets;
    double load_factor;
    int size;
    int capacity;
} HashMap;

/// @brief Create a new default hash map
/// @return A new default HashMap
HashMap new_HashMap();

/// @brief Free the resources associated with `map`. (Will not free `map` itself).
/// @param map A pointer to the map to delete
void delete_HashMap(HashMap *map);

/// @brief Get a value from a hashmap associated with `key`
/// @param map A pointer to the map to get the value from
/// @param key The key to the map
/// @return The value in the map if and entry exists, otherwise -1
int get_map(HashMap *map, char *key);

/// @brief Put a value into a hashmap at `key`
/// @param map A pointer to the map to put the value into
/// @param key The key to associate with the new value
/// @param value The value to put at `key`
void put_map(HashMap *map, char *key, int value);
