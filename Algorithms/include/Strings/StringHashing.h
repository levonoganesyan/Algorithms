#pragma once
#include<vector>
#include<string>
#include<type_traits>
namespace algo
{
    class StringHashing
    {
    private:
        const int m_prime = 331;
    private:
        long long m_mod;
        std::string m_str;
        std::vector<long long> m_hashes;
        std::vector<long long> m_primes;
    private:
        void build_hash();
    public:
        explicit StringHashing(const std::string& str, 
                      long long mod = LLONG_MAX);

        long long Get() const;
        long long Get(int i, int j) const;
        std::size_t Size() const;

    };
}