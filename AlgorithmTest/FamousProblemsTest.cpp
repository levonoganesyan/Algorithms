#include"pch.h"

#include"FamousProblems\AllProblems.h"

#include<string>
#include<vector>


TEST(MatrixMultiplicationTest, FamousProblemsTest)
{
    EXPECT_EQ(
        algo::MatrixMultProblem({ {10, 20}, {20, 30}, {30, 40}, {40, 30} }),
        30000
    );
    EXPECT_EQ(
        algo::MatrixMultProblem({ {40, 20}, {20, 30}, {30, 10}, {10, 30} }),
        26000
    );
    EXPECT_EQ(
        algo::MatrixMultProblem({ {10, 20}, {20, 30} }),
        6000
    );
}

TEST(LivenshteinTest, FamousProblemsTest)
{
    {
        std::string str1 = "dye";
        std::string str2 = "day";
        EXPECT_EQ(
            algo::Livenshtein(str1, str2),
            2
        );
    }
    {
        std::string str1 = "exponential";
        std::string str2 = "polynomial";
        EXPECT_EQ(
            algo::Livenshtein(str1, str2),
            6
        );
    }
    {
        std::string str1 = "kitten";
        std::string str2 = "sitting";
        EXPECT_EQ(
            algo::Livenshtein(str1, str2),
            3
        );
    }
    {
        std::string str1 = "saturday";
        std::string str2 = "sunday";
        EXPECT_EQ(
            algo::Livenshtein(str1, str2),
            3
        );
    }
}
TEST(LISTest, FamousProblemsTest)
{
    {
        std::vector<int> arr{ 0, 8, 4, 12, 2, 10, 6,
                              14, 1, 9, 5, 13, 3, 11, 7, 15 };
        EXPECT_EQ(algo::LIS(arr), 6);
    }
    {
        std::vector<int> arr{ 1,2,3,4,5,6,7 };
        EXPECT_EQ(algo::LIS(arr), 7);
    }
    {
        std::vector<int> arr{ 9, 7, 5, 3, 2, 1 };
        EXPECT_EQ(algo::LIS(arr), 1);
    }
    {
        std::vector<int> arr{ 1, 2, 1, 6, 1, 8, 1, 9, 
                                3, 10, 4, 5, 6, 7 };
        EXPECT_EQ(algo::LIS(arr), 7);
    }
}

TEST(LCSTest, FamousProblemsTest)
{
    {
        std::string str1 = "agcat";
        std::string str2 = "gac";
        EXPECT_EQ(
            algo::LCS(str1, str2),
            2
        );
    }
    {
        std::string str1 = "XMJYAUZ";
        std::string str2 = "MZJAWXU";
        EXPECT_EQ(
            algo::LCS(str1, str2),
            4
        );
    }
    {
        std::string str1 = "aaaa";
        std::string str2 = "aaaa";
        EXPECT_EQ(
            algo::LCS(str1, str2),
            4
        );
    }
    {
        std::string str1 = "abaaa";
        std::string str2 = "abababa";
        EXPECT_EQ(
            algo::LCS(str1, str2),
            5
        );
    }
    
}

