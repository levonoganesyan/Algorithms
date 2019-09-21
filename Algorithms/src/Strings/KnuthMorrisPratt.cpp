#include<Strings/KnuthMorrisPratt.h>

namespace algo
{
    void KnuthMorrisPratt::calculate()
    {
        auto prefix = m_prefix.Get();
        for (int i = m_first_size + 1; i < prefix.size(); ++i)
        {
            if (prefix[i] == m_first_size)
            {
                m_occurs.push_back(i - 2 * m_first_size);
            }
        }
    }
    KnuthMorrisPratt::KnuthMorrisPratt(const std::string& where,
                                            const std::string& what)
        : m_prefix(what + "#" + where)
        , m_first_size(what.size())
    {
        calculate();
    }
    std::vector<int> KnuthMorrisPratt::Get() const
    {
        return m_occurs;
    }
}
