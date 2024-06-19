#include "hashmap.hpp"

#include <gtest/gtest.h>

TEST(HashMap, Template)
{
    smol::HashMap<int, int> map;

    for (int i = 0; i < 32; ++i)
    {
        map.put(i, i * 2);
    }

    EXPECT_EQ(map.get(5), 10);

    try
    {
        map.get(45);
        FAIL() << "Expected HashMap::get to fail";
    } catch (...)
    {
    }
}
