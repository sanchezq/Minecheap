#include "Maths/vec4.h"
#include <cmath>
#include <cassert>

namespace Core
{
	namespace Maths
	{
		vec4::vec4(float x, float y, float z, float w) :
			m_x(x),
			m_y(y),
			m_z(z),
			m_w(w)
		{
		}

		void vec4::Homogenize()
		{
			if (m_w != 0)
			{
				m_x /= m_w;
				m_y /= m_w;
				m_z /= m_w;
				m_w = 1.f;
			}
		}

		float vec4::GetMagnitude() const
		{
			vec4 copy = *this;
			copy.Homogenize();

			return sqrtf((copy.m_x * copy.m_x + copy.m_y * copy.m_y + copy.m_z * copy.m_z));
			// ignoring m_w
		}

		void vec4::Normalize()
		{
			float magnitude = GetMagnitude();
			m_x = m_x / magnitude;
			m_y = m_y / magnitude;
			m_z = m_z / magnitude;
			// ignoring m_w
		}

		vec4 vec4::Cross(vec4 const& other) const
		{
			return vec4{ m_y * other.m_z - m_z * other.m_y,
						-(m_x * other.m_z - m_z * other.m_x),
						m_x * other.m_y - m_y * other.m_x };
		}

		float vec4::Dot(vec4 const& other) const
		{
			return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
		}

		float vec4::GetDeterminant(vec4 const& other) const
		{
			return m_y * other.m_z - m_z * other.m_y - (m_x * other.m_z - m_z * other.m_x) + m_x * other.m_y - m_y * other.m_x;
		}

		vec4& vec4::operator=(vec4 const& other)
		{
			m_w = other.m_w;
			m_x = other.m_x;
			m_y = other.m_y;
			m_z = other.m_z;

			return *this;
		}

		float vec4::operator[](size_t index) const
		{
			switch (index)
			{
			case 0:
				return m_x;
			case 1:
				return m_y;
			case 2:
				return m_z;
			case 3:
				return m_w;
			default:
				assert(false); // kill function;
				return 0; // return 0 to remove warning
			}
		}

		float& vec4::operator[](size_t index)
		{
			switch (index)
			{
			case 0:
				return m_x;
			case 1:
				return m_y;
			case 2:
				return m_z;
			case 3:
				return m_w;
			default:
				assert(false); // kill function;
				return m_x; // return first value to remove warning
			}
		}

		vec4 vec4::operator+(vec4 const& other) const
		{
			vec4 sum{
				this->m_x + other.m_x,
				this->m_y + other.m_y,
				this->m_z + other.m_z,
				this->m_w + other.m_w
			};
			return sum;
		}

		vec4 vec4::operator+=(vec4 const& other)
		{
			this->m_x += other.m_x;
			this->m_y += other.m_y;
			this->m_z += other.m_z;
			this->m_w += other.m_w;
			return *this;
		}

		vec4 vec4::operator-(vec4 const& other) const
		{
			vec4 difference{
				this->m_x - other.m_x,
				this->m_y - other.m_y,
				this->m_z - other.m_z,
				this->m_w - other.m_w
			};

			return difference;
		}

		vec4 vec4::operator-=(vec4 const& other)
		{
			this->m_x -= other.m_x;
			this->m_y -= other.m_y;
			this->m_z -= other.m_z;
			this->m_w -= other.m_w;
			return *this;
		}

		vec4 vec4::operator*(float const& scalar) const
		{
			vec4 product{
				this->m_x * scalar,
				this->m_y * scalar,
				this->m_z * scalar,
				this->m_w * scalar
			};

			return product;
		}

		vec4 vec4::operator*(Core::Maths::mat4 const& matrix)
		{
			float x = this->m_x * matrix[0][0] + this->m_y * matrix[0][1] + this->m_z * matrix[0][2] + this->m_w * matrix[0][3];
			float y = this->m_x * matrix[1][0] + this->m_y * matrix[1][1] + this->m_z * matrix[1][2] + this->m_w * matrix[1][3];
			float z = this->m_x * matrix[2][0] + this->m_y * matrix[2][1] + this->m_z * matrix[2][2] + this->m_w * matrix[2][3];
			float w = this->m_x * matrix[3][0] + this->m_y * matrix[3][1] + this->m_z * matrix[3][2] + this->m_w * matrix[3][3];
			return vec4(x, y, z, w);
		}

		vec4 vec4::operator*=(float const& scalar)
		{
			this->m_x *= scalar;
			this->m_y *= scalar;
			this->m_z *= scalar;
			this->m_w *= scalar;

			return *this;
		}
	}
}