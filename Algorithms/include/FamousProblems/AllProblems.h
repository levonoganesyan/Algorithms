#pragma once

#include<string>
#include<vector>
#include<type_traits>
#include<algorithm>
#include<Utils.h>
#include<Defines.h>
namespace algo
{
    template<typename T>
    int LIS(const T& seq);
    template<typename T>
    int LCS(const T& seq1, const T& seq2);
    template<typename T>
    int Livenshtein(const T& seq1, const T& seq2);

    using MatrixSize = std::pair<int, int>;
    using MatricesSize = std::vector<MatrixSize>;
    int MatrixMultProblem(const MatricesSize& sizes);
    int NQueenProblem(int n); // TODO
    int KnightsTour(int n); // TODO
}



namespace algo
{
    template<typename T>
    int LIS(const T& seq)
    {
        std::vector<int> dp(seq.size() + 1, Inf);
        dp[0] = -Inf;
        for (int i = 0; i < seq.size(); ++i)
        {
            int j = std::upper_bound(all(dp), seq[i]) - dp.begin();
            if (dp[j - 1] < seq[i] && seq[i] < dp[j])
            {
                dp[j] = seq[i];
            }
        }
        int ans = 0;
        for (int i = 0; i < dp.size(); ++i)
        {
            if (dp[i] < Inf)
            {
                ans = i;
            }
        }
        return ans;
    }
    template<typename T>
    int LCS(const T& seq1, const T& seq2)
    {
        std::vector<std::vector<int>> dp(seq1.size() + 1,
            std::vector<int>(seq2.size() + 1, Inf));
        for (int i = 0; i < seq1.size(); ++i)
        {
            dp[i][0] = 0;
        }
        for (int i = 0; i < seq2.size(); ++i)
        {
            dp[0][i] = 0;
        }
        for (int i = 1; i <= seq1.size(); ++i)
        {
            for (int j = 1; j <= seq2.size(); ++j)
            {
                if (seq1[i] == seq2[j])
                {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                }
                else
                {
                    dp[i][j] = std::max(dp[i][j - 1], dp[i - 1][j]);
                }
            }
        }
        return dp[seq1.size()][seq2.size()];
    }
    template<typename T>
    int Livenshtein(const T& seq1, const T& seq2)
    {
        std::vector<std::vector<int>> dist(seq1.size() + 1,
            std::vector<int>(seq2.size() + 1, Inf));
        dist[0][0] = 0;
        for (int i = 0; i < seq1.size(); ++i)
        {
            dist[i + 1][0] = dist[i][0] + 1;
        }
        for (int i = 0; i < seq2.size(); ++i)
        {
            dist[0][i + 1] = dist[0][i] + 1;
        }
        for (int i = 1; i <= seq1.size(); ++i)
        {
            for (int j = 1; j <= seq2.size(); ++j)
            {
                dist[i][j] = min(dist[i][j], dist[i - 1][j] + 1);
                dist[i][j] = min(dist[i][j], dist[i][j - 1] + 1);
                bool same_letter = seq1[i - 1] != seq2[j - 1];
                dist[i][j] = min(dist[i][j], dist[i - 1][j - 1] + same_letter);
            }
        }
        return dist[seq1.size()][seq2.size()];
    }
    int private_MatrixMultProblem(const MatricesSize& sizes,
                                         int i, int j)
    {
        if (i == j)
        {
            return 0;
        }
        int ans = Inf;
        for (int k = i; k < j; ++k)
        {
            int temp = private_MatrixMultProblem(sizes, i, k);
            temp += private_MatrixMultProblem(sizes, k + 1, j);
            temp += sizes[i].first * sizes[k + 1].first * sizes[j].second;
            ans = std::min(ans, temp);
        }
        return ans;
    }
    int algo::MatrixMultProblem(const MatricesSize& sizes)
    {
        return private_MatrixMultProblem(sizes, 0, sizes.size() - 1);
    }
}