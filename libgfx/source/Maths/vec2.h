#pragma once
#include "lib_Export.h"
namespace Core
{
	namespace Maths
	{
		class lib_API vec2
		{
		public:
			vec2() = delete;
			vec2(float s, float t);
			~vec2() = default;

			float operator[](size_t index) const;
			float& operator[](size_t index);

			float m_s = 0.f;
			float m_t = 0.f;
		};
	}
}