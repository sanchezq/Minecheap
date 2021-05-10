#include"Maths/mat3.h"
#include <cassert>
namespace Core
{
	namespace Maths
	{
		mat3::mat3(float dgValue):
			m_matrix{ dgValue, 0.f, 0.f,
					  0.f, dgValue, 0.f,
					  0.f, 0.f, dgValue }
		{
		}

		mat3::mat3(float a, float b, float c, float d, float e, float f, float g, float h, float i):
			m_matrix{a,b,c,d,e,f,g,h,i}
		{
		}

		mat3::mat3(mat4 other):
			m_matrix{other[0][0], other[0][1], other[0][2],
					 other[1][0], other[1][1], other[1][2],
					 other[2][0], other[2][1], other[2][2]}
		{
		}

		float mat3::GetDeterminant(mat3 other)
		{
			float x = other[0][0] * (other[1][1] * other[2][2] - other[1][2] * other[2][1]);
			float y = other[0][1] * (other[1][0] * other[2][2] - other[1][2] * other[2][0]);
			float z = other[0][2] * (other[1][1] * other[2][1] - other[1][1] * other[2][0]);
			return x - y + z;
		}

		mat3 mat3::TransposeMatrix(mat3 other)
		{
			return mat3{ other[0][0], other[0][1], other[0][2],
						 other[1][0], other[1][1], other[1][2],
						 other[2][0], other[2][1], other[2][2] };
		}

		mat3::row mat3::operator[](size_t index)
		{
#ifdef _DEBUG
			assert(index < 3);
#endif // _DEBUG

			return row(&m_matrix[index * 3]);
		}
		mat3::const_row mat3::operator[](size_t index) const
		{
#ifdef _DEBUG
			assert(index < 3);
#endif // _DEBUG
			return const_row(&m_matrix[index * 3]);
		}
		float& mat3::row::operator[](size_t columnIndex)
		{
#ifdef _DEBUG
			assert(columnIndex < 3);
#endif // _DEBUG

			return m_ptr[columnIndex];
		}

		float mat3::const_row::operator[](size_t columnIndex) const
		{
#ifdef _DEBUG
			assert(columnIndex < 3);
#endif // _DEBUG

			return m_ptr[columnIndex];
		}
	}
}