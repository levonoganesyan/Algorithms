#include<Strings/Prefix-Function.h>
#include<algorithm>
namespace algo
{
    void Prefix_Function::calculate()
    {
        for (int i = 1; i < m_str.size(); ++i)
        {
            int j = m_prefix[i - 1];
            while (j > 0 && s[i] != s[j])
            {
                j = m_prefix[j - 1];
            }
            if (s[i] == s[j])
            {
                ++j;
            }
            m_prefix[i] = j;
        }
    }

    Prefix_Function::Prefix_Function(const std::string& str)
        : m_str(str)
        , m_prefix(str.size())
    {
        calculate();
    }

    std::vector<int> Prefix_Function::Get() const
    {
        return m_prefix;
    }


}