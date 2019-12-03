#include"pch.h"

#include"Math/Math.h"




TEST(BinPowMatrixMulTest, MathTest)
{

    algo::Matrix<int> mat{ {1, 1}, { 1, 0 } };
    algo::Matrix<int> neutral{ {1, 0}, { 0, 1 } };
    algo::Matrix<int> fib{ {1, 1} };
    mat = algo::bin_pow(mat, 7, neutral, algo::matrix_mul<int>);
    fib = algo::matrix_mul(fib, mat);
    algo::Matrix<int> etalon{ {34, 21} };
    EXPECT_EQ(fib, etalon);
}
TEST(EulerFunctionTest, MathTest)
{ 
    for(int i = 2; i < 1000; ++i)
        EXPECT_EQ(algo::euler(i), algo::fast_euler(i));
}