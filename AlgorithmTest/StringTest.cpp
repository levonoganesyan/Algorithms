#include"pch.h"

#include"Strings/StringHashing.h"
#include"Strings/ZFunction.h"
#include"Strings/PrefixFunction.h"
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

TEST(PrefixFunctionTest, StringTest)
{
    {
        algo::PrefixFunction p("abcabcd");
        std::vector<int> etalon{ 0, 0, 0, 1, 2, 3, 0 };
        EXPECT_EQ(p.Get(), etalon);
    }
    {
        algo::PrefixFunction p("aabaaab");
        std::vector<int> etalon{ 0, 1, 0, 1, 2, 2, 3 };
        EXPECT_EQ(p.Get(), etalon);
    }
    {
        algo::PrefixFunction p("abaabaabababaaabbbabababab");
        std::vector<int> etalon{ 0, 0, 1, 1, 2, 3, 4,
                                 5, 6, 2, 3, 2, 3, 4,
                                 1, 2, 0, 0, 1, 2, 3,
                                 2, 3, 2, 3, 2 };
        EXPECT_EQ(p.Get(), etalon);
    }


}

TEST(KnuthMorrisPrattTest, StringTest)
{
    {
        algo::PrefixFunction p("abcabcd");
        std::vector<int> etalon{ 0, 0, 0, 1, 2, 3, 0 };
        EXPECT_EQ(p.Get(), etalon);
    }
    {
        algo::PrefixFunction p("aabaaab");
        std::vector<int> etalon{ 0, 1, 0, 1, 2, 2, 3 };
        EXPECT_EQ(p.Get(), etalon);
    }
    {
        algo::PrefixFunction p("abaabaabababaaabbbabababab");
        std::vector<int> etalon{ 0, 0, 1, 1, 2, 3, 4,
                                 5, 6, 2, 3, 2, 3, 4,
                                 1, 2, 0, 0, 1, 2, 3,
                                 2, 3, 2, 3, 2 };
        EXPECT_EQ(p.Get(), etalon);
    }
}
