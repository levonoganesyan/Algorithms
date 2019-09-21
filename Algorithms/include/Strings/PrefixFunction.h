#pragma once

#include<string>
#include<vector>

namespace algo
{
    class PrefixFunction
    {
    private:
        std::string m_str;
        std::vector<int> m_prefix;
        void calculate();
    public:
        PrefixFunction(const std::string& str);
        std::vector<int> Get() const;
    };
}
