#include <algorithm>
#include <gtest/gtest.h>
#include <sstream>
#include <vec.hpp>

TEST(Vec, Construction)
{
    char str_arr[] = "hello";
    smol::vec<char> str_vec{'h', 'e', 'l', 'l', 'o', '\0'};

    EXPECT_STREQ(str_arr, str_vec.ptr());
}

TEST(Vec, Capacity)
{
    smol::vec<char> str_vec{'h', 'e', 'l', 'l', 'o', '\0'};
    EXPECT_EQ(str_vec.capacity(), 6);

    str_vec.reserve(10);
    EXPECT_EQ(str_vec.capacity(), 14);
}

TEST(Vec, Assignment)
{
    smol::vec<char> str_vec1{'h', 'e', 'l', 'l', 'o', '\0'};
    smol::vec<char> str_vec2;

    str_vec2 = str_vec1;

    EXPECT_STREQ(str_vec1.ptr(), str_vec2.ptr());
    EXPECT_NE(str_vec1.ptr(), str_vec2.ptr());
}

TEST(Vec, Push)
{
    smol::vec<int> vector;
    smol::vec<int> vector_list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    for (int i = 0; i < 10; ++i)
    {
        vector.push(i);
    }

    EXPECT_EQ(vector.len, 10);
    EXPECT_EQ(vector.capacity(), 12);
}

TEST(Vec, Pop)
{
    smol::vec<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    EXPECT_EQ(list.pop(), 9);
    EXPECT_EQ(list.size(), 9);
    EXPECT_EQ(list.capacity(), 10);
}

TEST(Vec, ForwardIterator)
{
    smol::vec<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::stringstream out;

    for (int i : list)
    {
        out << i;
    }

    EXPECT_STREQ(out.str().c_str(), "0123456789");
}

TEST(Vec, OperatorEq)
{
    smol::vec<int> list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    smol::vec<int> list_copy(list);

    EXPECT_EQ(list, list_copy);
}

TEST(Vec, RandomIterator)
{
    smol::vec<int> list{5, 1, 8, 0, 9, 3};
    smol::vec<int> sorted{0, 1, 3, 5, 8, 9};

    std::sort(list.begin(), list.end());

    EXPECT_EQ(list, sorted);
}
