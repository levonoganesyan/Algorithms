#pragma once

#include<string>
#include<vector>
#include<Strings/PrefixFunction.h>

namespace algo
{
    class KnuthMorrisPratt
    {
    private:
        std::vector<int> m_occurs;
        PrefixFunction m_prefix;
        int m_first_size;
        void calculate();
    public:
        KnuthMorrisPratt(const std::string& str1,
                            const std::string& str2);
        std::vector<int> Get() const;
    };
}
