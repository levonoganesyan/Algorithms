#include<Strings/StringHashing.h>

namespace algo
{
    void StringHashing::build_hash()
    {
        m_primes[0] = 1;
        for (int i = 0; i < m_str.size(); ++i)
        {
            m_hashes[i + 1] = m_hashes[i] * m_prime + m_str[i];
            m_hashes[i + 1] %= m_mod;
            m_primes[i + 1] = m_primes[i] * m_prime;
            m_primes[i + 1] %= m_mod;
        }
    }
    StringHashing::StringHashing(const std::string& str, long long mod)
        : m_str(str)
        , m_hashes(str.size() + 1)
        , m_primes(str.size() + 1)
        , m_mod(mod)
    {
        build_hash();
    }
    long long StringHashing::Get() const
    {
        return Get(0, m_str.size() - 1);
    }
    long long StringHashing::Get(int i, int j) const
    {
        long long hash = m_hashes[j + 1];
        hash -= (m_hashes[i] * m_primes[j - i + 1]) % m_mod;
        if (hash < 0)
            hash += m_mod;
        return hash;
    }
    std::size_t StringHashing::Size() const
    {
        return m_str.size();
    }
}