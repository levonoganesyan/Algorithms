#pragma once

#include<string>
#include<vector>

namespace algo
{
    class Prefix_Function
    {
    private:
        std::string m_str;
        std::vector<int> m_prefix;
        void calculate();
    public:
        Prefix_Function(const std::string& str);
        std::vector<int> Get() const;
    };
}
