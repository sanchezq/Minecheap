#pragma once
#include "lib_Export.h"
namespace Core
{
	namespace Maths
	{
		class lib_API mat4
		{
		public:
			struct row
			{
				row(float* ptr) : m_ptr(ptr) {}
				float* m_ptr;

				float& operator[](size_t columIndex);
			};
			struct const_row
			{
				const_row(float const* ptr) : m_ptr(ptr) {}
				float const* m_ptr;

				float operator[](size_t columIndex) const;
			};

			mat4() = default;
			explicit mat4(float diagonalValue);

			mat4(float a, float b, float c, float d,
				float e, float f, float g, float h,
				float i, float j, float k, float l,
				float m, float n, float o, float p);
			~mat4() = default;

			static mat4 Identity();
			static mat4 TransposeMatrix(mat4& other);

			mat4 operator*(mat4 const& other) const;
			row operator[](size_t index);
			const_row operator[](size_t index) const;

			float m_matrix[16] = { 0.f, 0.f, 0.f, 0.f,
									0.f, 0.f, 0.f, 0.f,
									0.f, 0.f, 0.f, 0.f,
									0.f, 0.f, 0.f, 0.f };
		private:
		};
	}
}