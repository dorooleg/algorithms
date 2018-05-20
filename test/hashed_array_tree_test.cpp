#include "gtest/gtest.h"
#include <containers/hashed_array_tree.hpp>

TEST(HashedArrayTree, Empty)
{
   hashed_array_tree<int> v;
   ASSERT_TRUE(v.empty());
   ASSERT_EQ(v.size(), 0);
}

TEST(HashedArrayTree, PushBack)
{
   hashed_array_tree<int> v;
   v.push_back(1);
   ASSERT_FALSE(v.empty());
   ASSERT_EQ(v.back(), 1);
}


int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
