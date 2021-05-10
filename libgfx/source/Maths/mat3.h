#pragma once
#include "mat4.h"
namespace Core
{
	namespace Maths
	{
		class lib_API mat3
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

			mat3() = default;
			explicit mat3(float dgValue);

			mat3(float a, float b, float c,
				 float d, float e, float f, 
				 float g, float h, float i);

			mat3(mat4 other);
			~mat3() = default;

			static float GetDeterminant(mat3 other);
			static mat3 TransposeMatrix(mat3 other);

			row operator[](size_t index);
			const_row operator[](size_t index) const;
			float m_matrix[9] = { 0.f, 0.f, 0.f,
								  0.f, 0.f, 0.f,
								  0.f, 0.f, 0.f};
		private:

		};

	}
}