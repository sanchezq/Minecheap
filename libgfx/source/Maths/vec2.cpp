#include "Maths/vec2.h"
#include <cassert>
namespace Core
{
	namespace Maths
	{//TODO substituir pelo meu proprio assert
		vec2::vec2(float s, float t) :
			m_s(s),
			m_t(t)
		{
		}

		float& vec2::operator[](size_t index)
		{
			switch (index)
			{
			case 0:
				return m_s;
			case 1:
				return m_t;
			default:
				assert(false); // kill function;
				return m_s; // return first value to remove warning
			}
		}

		float vec2::operator[](size_t index) const
		{
			switch (index)
			{
			case 0:
				return m_s;
			case 1:
				return m_t;
			default:
				assert(false); // kill function;
				return 0; // return 0 to remove warning
			}
		}
	}
}