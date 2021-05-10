#pragma once
#include "vec4.h"
namespace Core
{
	namespace Maths
	{
		class lib_API vec3
		{
		public:
			vec3(const float x, const float y, const float z = 0.f);
			vec3() = delete;
			~vec3() = default;

			float GetMagnitude() const;
			void Set(const float x, const float y, const float z);
			vec3& Normalize();
			vec3 Cross(vec3 const& other) const;
			float Dot(vec3 const& other) const;

			float operator[](size_t index) const;
			float& operator[](size_t index);
			vec3 operator+(vec3 const& other) const;
			vec3& operator+=(vec3 const& other);
			vec3& operator-=(vec3 const& other);
			vec3& operator=(vec4 const& vec);
			vec3 operator*(vec3 const& other);
			vec3 operator-() const;
			vec3 operator-(vec3 const& other) const;
			vec3 operator*(float scalar) const;
			vec3& operator*=(float scalar);
			vec3 operator*(Core::Maths::mat4 const& matrix);

			float m_x = 0.f;
			float m_y = 0.f;
			float m_z = 0.f;
		};
	}
}