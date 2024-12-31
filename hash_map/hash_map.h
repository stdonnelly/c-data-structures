#pragma once

/// @brief Union of a `long long` and a `void*`.
///
/// This is used by the hashmap to hold a primitive or a pointer to arbitrary data.
/// I didn't typedef this due to likely name collision.
union Value
{
    long long val;
    void *ptr;
};

/// @brief Entry in a HashMap
typedef struct MapEntry
{
    union Value value;
    char *key;
    struct MapEntry *next;
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

/// @brief Free the resources associated with `map`. (Will not free `map` itself).
///
/// This will also call free on each MapEntry.value.ptr
/// @param map A pointer to the map to delete
void delete_HashMap_free_values(HashMap *map);

/// @brief Get a value from a hashmap associated with `key`
/// @param map A pointer to the map to get the value from
/// @param key The key to the map
/// @param value Out: The value at `key` if it exists. Will not be set if no value exists for `key`
/// @return 1 if found, 0 if no entry exists for `key`.
int get_map(HashMap *map, char *key, union Value *value);

/// @brief Put a value into a hashmap at `key`
/// @param map A pointer to the map to put the value into
/// @param key The key to associate with the new value
/// @param value The value to put at `key`
void put_map(HashMap *map, char *key, union Value value);
