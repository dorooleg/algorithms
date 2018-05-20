#include "gtest/gtest.h"
#include <containers/stack.hpp>

TEST(Stack, Empty)
{
    stack<bool> s;
    ASSERT_EQ(s.size(), 0);
}

TEST(Stack, Push)
{
    stack<int> s;
    s.push(10);
    ASSERT_EQ(s.size(), 1);
    ASSERT_EQ(s.top(), 10);
    s.push(20);
    ASSERT_EQ(s.top(), 20);
}

TEST(Stack, PushPop)
{
    stack<int> s;
    s.push(10);
    ASSERT_EQ(s.top(), 10);
    s.pop();
    ASSERT_EQ(s.size(), 0);
}

TEST(Stack, ConstType)
{
    stack<const int> s;
    s.push(10);
    ASSERT_EQ(s.top(), 10);
}

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
