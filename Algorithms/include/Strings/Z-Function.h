#pragma once

#include<string>
#include<vector>

namespace algo
{
    class Z_Function
    {
    private:
        std::string m_str;
        std::vector<int> m_z;
        void calculate();
    public:
        Z_Function(const std::string& str);
        std::vector<int> GetZ() const;
    };
}
