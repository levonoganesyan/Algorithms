#include<Strings/PrefixFunction.h>
#include<algorithm>
namespace algo
{
    void PrefixFunction::calculate()
    {
        for (int i = 1; i < m_str.size(); ++i)
        {
            int j = m_prefix[i - 1];
            while (j > 0 && m_str[i] != m_str[j])
            {
                j = m_prefix[j - 1];
            }
            if (m_str[i] == m_str[j])
            {
                ++j;
            }
            m_prefix[i] = j;
        }
    }

    PrefixFunction::PrefixFunction(const std::string& str)
        : m_str(str)
        , m_prefix(str.size())
    {
        calculate();
    }

    std::vector<int> PrefixFunction::Get() const
    {
        return m_prefix;
    }


}