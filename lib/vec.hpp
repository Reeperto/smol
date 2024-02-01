#pragma once

#include "iterator.hpp"

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <initializer_list>

namespace smol
{
template <typename T> struct vec
{
    T *values;
    size_t len;
    size_t cap;

    vec() : values(new T[1]), len(0), cap(1){};

    vec(std::initializer_list<T> init_vals)
    {
        len = cap = init_vals.size();
        values = new T[len];

        int i = 0;
        const T *val_ptr = init_vals.begin();
        const T *end_ptr = init_vals.end();

        while (val_ptr != end_ptr)
        {
            values[i] = *val_ptr;
            ++i, ++val_ptr;
        }
    }

    // Copy Constructor
    vec(vec &v) : values(new T[v.cap]), len(v.len), cap(v.cap)
    {
        std::memcpy(this->values, v.values, v.len * sizeof(T));
    }

    // Destructor
    ~vec() { delete[] values; }

    // Copy Assignmnet
    vec &operator=(vec &v)
    {
        if (cap < v.cap)
        {
            delete[] values;
            values = new T[v.cap];
            cap = v.cap;
        }

        std::memcpy(values, v.values, v.len * sizeof(T));

        return *this;
    }

    T const &operator[](size_t index) const { return values[index]; }

    bool operator==(const vec &other) const
    {
        if (len != other.len)
        {
            return false;
        }

        for (int i = 0; i < len; ++i)
        {
            if (values[i] != other.values[i])
            {
                return false;
            }
        }

        return true;
    }

    size_t capacity() { return cap; }
    size_t size() { return len; }
    T *ptr() const { return values; }

    void clear() { len = 0; }

    void push(T elem)
    {
        if (len + 1 > cap)
        {
            reserve(len + 1);
        }

        values[len++] = elem;
    }

    T pop() { return std::move(values[--len]); }

    void reserve(size_t new_len)
    {
        while (cap < new_len)
        {
            cap = (cap << 1) - (cap >> 1);
        }

        T *temp_buf = new T[cap];
        std::memcpy(temp_buf, values, sizeof(T) * len);
        delete[] values;
        values = temp_buf;
    }

    RandomIterator<T> begin() { return RandomIterator(values); }
    RandomIterator<T> end() { return RandomIterator(values + len); }
};
} // namespace smol
