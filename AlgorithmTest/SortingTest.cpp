#include"pch.h"

#include"Sortings/Sorting.h"


TEST(SortingTest, SortingTest)
{
    auto origin = getRandomVector(6, 0, 9);
    auto sorted_origin = origin;
    std::sort(sorted_origin.begin(), sorted_origin.end());

    {
        auto copy = origin;
        algo::BubbleSort(copy.begin(), copy.end());
        EXPECT_EQ(copy, sorted_origin);
    }
    {
        auto copy = origin;
        algo::SelectionSort(copy.begin(), copy.end());
        EXPECT_EQ(copy, sorted_origin);
    }
    {
        auto copy = origin;
        algo::InsertionSort(copy.begin(), copy.end());
        EXPECT_EQ(copy, sorted_origin);
    }
    {
        auto copy = origin;
        algo::RadixSort(copy.begin(), copy.end());
        EXPECT_EQ(copy, sorted_origin);
    }
    {
        auto copy = origin;
        algo::HeapSort(copy.begin(), copy.end());
        EXPECT_EQ(copy, sorted_origin);
    }
    {
        auto copy = origin;
        algo::MergeSort(copy.begin(), copy.end());
        EXPECT_EQ(copy, sorted_origin);
    }
    {
        auto copy = origin;
        algo::QuickSort(copy.begin(), copy.end());
        EXPECT_EQ(copy, sorted_origin);
    }
}