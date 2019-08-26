#include"pch.h"

#include"DataStructures/SegmentTree.h"
#include<numeric>
#include<cmath>

int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }
int sum_on_vector(const std::vector<int>& vec, int i, int j)
{
    int sum = 0;
    while (i <= j)
    {
        sum += vec[i++];
    }
    return sum;
}
int mul_on_vector(const std::vector<int>& vec, int i, int j)
{
    int mul = 1;
    while (i <= j)
    {
        mul *= vec[i++];
    }
    return mul;
}
int min_on_vector(const std::vector<int>& vec, int i, int j)
{
    int g = vec[i++];
    while (i <= j)
    {
        g = std::min(g, vec[i++]);
    }
    return g;
}
int max_on_vector(const std::vector<int>& vec, int i, int j)
{
    int g = vec[i++];
    while (i <= j)
    {
        g = std::max(g, vec[i++]);
    }
    return g;
}
int gcd_on_vector(const std::vector<int>& vec, int i, int j)
{
    int g = vec[i++];
    while (i <= j)
    {
        g = gcd(g, vec[i++]);
    }
    return g;
}



TEST(SegmentTree, DataStructures)
{
    std::mt19937 rand_function(time(0));
    // sum
    for (int i = 0; i < 10; ++i)
    {
        std::vector<int> vec = getRandomVector(1000, 1, 100);
        algo::SegmentTree<int> tree(vec, std::plus<int>(), 0);
        tree.build_tree();
        std::uniform_int_distribution<int> uid(0, vec.size() - 1);
        int a = uid(rand_function);
        int b = uid(rand_function);
        if (a > b)
            std::swap(a, b);
        EXPECT_EQ(tree.query(a, b), sum_on_vector(vec, a, b));
        tree.update(a, vec[a] + 1);
    }
    // product
    for (int i = 0; i < 10; ++i)
    {
        std::vector<int> vec = getRandomVector(1000, -1, 1);
        algo::SegmentTree<int> tree(vec, std::multiplies<int>(), 1);
        tree.build_tree();
        std::uniform_int_distribution<int> uid(0, vec.size() - 1);
        int a = uid(rand_function);
        int b = uid(rand_function);
        if (a > b)
            std::swap(a, b);
        EXPECT_EQ(tree.query(a, b), mul_on_vector(vec, a, b));
        tree.update(a, vec[a] + 1);
    }
    // min
    for (int i = 0; i < 10; ++i)
    {
        std::vector<int> vec = getRandomVector(1000, -1111, 1111);
        const int& (*operation)(const int&, const int&) = std::min<int>;
        algo::SegmentTree<int> tree(vec, operation, 1111);
        tree.build_tree();
        std::uniform_int_distribution<int> uid(0, vec.size() - 1);
        int a = uid(rand_function);
        int b = uid(rand_function);
        if (a > b)
            std::swap(a, b);
        EXPECT_EQ(tree.query(a, b), min_on_vector(vec, a, b));
        tree.update(a, vec[a] + 1);
    }
    // max
    for (int i = 0; i < 10; ++i)
    {
        std::vector<int> vec = getRandomVector(1000, -1111, 1111);
        const int& (*operation)(const int&, const int&) = std::max<int>;
        algo::SegmentTree<int> tree(vec, operation, -1111, algo::SegmentTree<int>::UpdateType::Sum);
        tree.build_tree();
        std::uniform_int_distribution<int> uid(0, vec.size() - 1);
        int a = uid(rand_function);
        int b = uid(rand_function);
        if (a > b)
            std::swap(a, b);
        EXPECT_EQ(tree.query(a, b), max_on_vector(vec, a, b));
        tree.update(a, vec[a] + 1);
    }
    // gcd
    for (int i = 0; i < 10; ++i)
    {
        std::vector<int> vec = getRandomVector(1000, 1, 100);
        algo::SegmentTree<int> tree(vec, [](int a, int b) { return gcd(a, b); }, 0);
        tree.build_tree();
        std::uniform_int_distribution<int> uid(0, vec.size() - 1);
        int a = uid(rand_function);
        int b = uid(rand_function);
        if (a > b)
            std::swap(a, b);
        EXPECT_EQ(tree.query(a, b), gcd_on_vector(vec, a, b));
        tree.update(a, vec[a] + 1);
    }
}