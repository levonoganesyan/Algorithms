#pragma once

#include<string>
#include<Utils.h>
namespace algo
{
    class Sudoku
    {
    public:
        Sudoku(const std::string& sudoku);
        Sudoku(const Matrix<int>& sudoku);
    };
}