#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <bitset>
#include <algorithm>
#include <sstream>
#include <Math/Math.h>
using namespace std;

// Test z-function
// Test Khun

int main()
{
    algo::Matrix<int> mat{ {1, 1}, { 1, 0 } };
    algo::Matrix<int> neutral{ {1, 0}, { 0, 1 } };
    algo::Matrix<int> fib { {1, 1} };
    mat = algo::bin_pow(mat, 7, neutral, algo::matrix_mul<int>);
    fib = algo::matrix_mul(fib, mat);
}



