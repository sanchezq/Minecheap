#include "Maths/mat4.h"
#include <cassert>
namespace Core
{
	namespace Maths
	{
		mat4::mat4(float v) :
			m_matrix{ v,0,0,0,
						0,v,0,0,
						0,0,v,0,
						0,0,0,v }
		{
		}

		mat4::mat4(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) :
			m_matrix{ a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p }
		{
		}

		mat4 mat4::Identity()
		{
			return mat4(1.f);
		}

		mat4 mat4::TransposeMatrix(mat4& other)
		{
			
			return { other[0][0], other[1][0], other[2][0], other[3][0],
					 other[0][1], other[1][1], other[2][1], other[3][1],
					 other[0][2], other[1][2], other[2][2], other[3][2],
					 other[0][3], other[1][3], other[2][3], other[3][3], };
		}

		mat4 mat4::operator*(mat4 const& other) const
		{
			mat4 product;
			for (size_t rowIndex = 0; rowIndex < 4; rowIndex++)
			{
				for (size_t columnnIndex = 0; columnnIndex < 4; columnnIndex++)
				{
					for (size_t a = 0; a < 4; a++)
					{
						product[rowIndex][columnnIndex] += (*this)[rowIndex][a] * other[a][columnnIndex];
					}
				}
			}
			return product;
		}

		mat4::row mat4::operator[](size_t rowIndex)
		{
#ifdef _DEBUG
			assert(rowIndex < 4);
#endif // _DEBUG

			return row(&m_matrix[rowIndex * 4]);
		}

		mat4::const_row mat4::operator[](size_t rowIndex) const
		{
#ifdef _DEBUG
			assert(rowIndex < 4);
#endif // _DEBUG

			return const_row(&m_matrix[rowIndex * 4]);
		}

		float& mat4::row::operator[](size_t columnIndex)
		{
#ifdef _DEBUG
			assert(columnIndex < 4);
#endif // _DEBUG

			return m_ptr[columnIndex];
		}

		float mat4::const_row::operator[](size_t columnIndex) const
		{
#ifdef _DEBUG
			assert(columnIndex < 4);
#endif // _DEBUG

			return m_ptr[columnIndex];
		}
	}
}