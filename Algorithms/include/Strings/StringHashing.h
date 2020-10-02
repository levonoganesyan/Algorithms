#pragma once
#include<vector>
#include<string>
#include<type_traits>
namespace algo
{
    class StringHashing
    {
    public:
        typedef unsigned long long HashType;
    private:
        const int m_prime = 331;
    private:
        HashType m_mod;
        std::string m_str;
        std::vector<HashType> m_hashes;
        std::vector<HashType> m_primes;
    private:
        void build_hash();
    public:
        explicit StringHashing(const std::string& str, 
                      HashType mod = ULLONG_MAX);

        HashType Get() const;
        HashType Get(int i, int j) const;
        std::size_t Size() const;

    };
}