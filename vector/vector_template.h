#pragma once

#include <stdlib.h>
#include <string.h>

// Macro to define a generic vector
#define DEF_VEC(T)                                                 \
    typedef struct T##_Vec                                         \
    {                                                              \
        T *arr;                                                    \
        size_t len;                                                \
        size_t cap;                                                \
    } T##_Vec;                                                     \
    void resize_##T##_Vec(T##_Vec *this, size_t new_cap)           \
    {                                                              \
        this->arr = realloc(this->arr, sizeof(T) * new_cap);       \
        this->cap = new_cap;                                       \
    }                                                              \
    void append_##T##_Vec(T##_Vec *this, T val)                    \
    {                                                              \
        if (this->len + 1 > this->cap)                             \
            resize_##T##_Vec(this, this->cap ? this->cap * 2 : 1); \
        *(this->arr + (this->len++)) = val;                        \
    }                                                              \
    T##_Vec new_##T##_Vec() { return (T##_Vec){NULL, 0, 0}; }
