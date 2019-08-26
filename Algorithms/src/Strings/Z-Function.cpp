#include<Strings/Z-Function.h>
#include<algorithm>
namespace algo
{
	void Z_Function::calculate()
	{
		for (int i = 1, l = 0, r = 0; i < m_str.size(); ++i)
		{
			if (i <= r)
			{
				m_z[i] = std::min(r - i + 1, m_z[i - l]);
			}
			while (i + m_z[i] < m_str.size() && m_str[i + m_z[i]] == m_str[m_z[i]])
			{
				++m_z[i];
			}
			if (i + m_z[i] - 1 > r)
			{
				l = i;
				r = i + m_z[i] - 1;
			}
		}
	}

	Z_Function::Z_Function(const std::string& str)
		: m_str(str)
		, m_z(str.size())
	{
		calculate();
	}

	std::vector<int> Z_Function::GetZ() const
	{
		return m_z;
	}


}