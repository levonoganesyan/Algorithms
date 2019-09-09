#include"pch.h"

#include"Strings/StringHashing.h"
#include"Strings/Z-Function.h"
#include<string>
#include<algorithm>

TEST(HashingTest, StringTest)
{
    {
        std::string test_string = "abacaba";
        std::string reverse_string = test_string;
        std::reverse(test_string.begin(), test_string.end());
        algo::StringHashing hash1(test_string);
        algo::StringHashing hash2(reverse_string);
        EXPECT_EQ(hash1.Get(), hash2.Get());
        EXPECT_EQ(hash1.Get(0, 2), hash2.Get(0, 2));
        EXPECT_EQ(hash1.Get(0, 2), hash2.Get(4, 6));
        EXPECT_EQ(hash1.Get(0, 2), hash1.Get(4, 6));
        EXPECT_EQ(hash1.Get(2, 4), hash2.Get(2, 4));
        EXPECT_EQ(hash1.Get(0, 0), 'a');
        EXPECT_EQ(hash1.Get(2, 2), 'a');
        EXPECT_EQ(hash1.Get(4, 4), 'a');
        EXPECT_EQ(hash1.Get(6, 6), 'a');
    }
}
