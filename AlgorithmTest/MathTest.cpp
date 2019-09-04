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