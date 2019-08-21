//
// pch.h
// Header for standard system include files.
//

#pragma once

#include "gtest/gtest.h"
#include<vector>
#include<random>
#include<ctime>

std::vector<int> getRandomVector(int n, int min = -1000, int max = 1000);

