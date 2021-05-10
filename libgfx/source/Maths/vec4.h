#pragma once
#include "mat4.h"
#include "lib_Export.h"
namespace Core
{
	namespace Maths
	{
		class lib_API vec4
		{
		public:
			vec4() = default;
			vec4(float x, float y, float z = 0.f, float w = 1.f);
			~vec4() = default;

			void Homogenize();
			float GetMagnitude() const;
			void Normalize();
			vec4 Cross(vec4 const& other) const;
			float Dot(vec4 const& other) const;
			float GetDeterminant(vec4 const& other) const;

			vec4& operator=(vec4 const& other);
			float operator[](size_t index) const;
			float& operator[](size_t index);
			vec4 operator+(vec4 const& other) const;
			vec4 operator+=(vec4 const& other);
			vec4 operator-(vec4 const& other) const;
			vec4 operator-=(vec4 const& other);
			vec4 operator*(float const& scalar) const;
			vec4 operator*(Core::Maths::mat4 const& matrix);
			vec4 operator*=(float const& scalar);

			float m_x = 0.f;
			float m_y = 0.f;
			float m_z = 0.f;
			float m_w = 1.f;
		};
	}
}