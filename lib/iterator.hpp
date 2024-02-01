#pragma once
#include <iterator>

namespace smol
{
template <typename T> struct RandomIterator
{
    using self = RandomIterator;
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    RandomIterator(pointer ptr) : ptr(ptr) {}

    reference operator*() { return *ptr; }
    pointer operator->() { return ptr; }

    self &operator++()
    {
        ++ptr;
        return *this;
    }

    self &operator--()
    {
        --ptr;
        return *this;
    }

    self &operator++(int)
    {
        self tmp = *this;
        ++(*this);
        return tmp;
    }

    self &operator--(int)
    {
        self tmp = *this;
        --(*this);
        return tmp;
    }

    self operator+(difference_type n) { return self(ptr + n); }
    self operator-(difference_type n) { return self(ptr - n); }

    difference_type operator-(const self &rhs) { return ptr - rhs.ptr; }

    friend bool operator>(const self &lhs, const self &rhs)
    {
        return lhs.ptr > rhs.ptr;
    }

    friend bool operator<(const self &lhs, const self &rhs)
    {
        return lhs.ptr < rhs.ptr;
    }

    friend bool operator==(const self &lhs, const self &rhs)
    {
        return lhs.ptr == rhs.ptr;
    }

    friend bool operator!=(const self &lhs, const self &rhs)
    {
        return lhs.ptr != rhs.ptr;
    }

  private:
    pointer ptr;
};
} // namespace smol
