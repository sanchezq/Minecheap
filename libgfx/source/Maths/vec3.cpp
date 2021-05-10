#include "Maths/vec3.h"
#include <cmath>
#include <cassert>
namespace Core
{
	namespace Maths
	{//TODO substituir pelo meu proprio assert
		vec3::vec3(const float x, const float y, const float z) :
			m_x(x),
			m_y(y),
			m_z(z)
		{
		}

		float vec3::GetMagnitude() const
		{
			return sqrtf((m_x * m_x + m_y * m_y + m_z * m_z));
		}

		void vec3::Set(const float x, const float y, const float z)
		{
			m_x = x;
			m_y = y;
			m_z = z;
		}

		vec3& vec3::Normalize()
		{
			float magnitude = GetMagnitude();
			m_x = m_x / magnitude;
			m_y = m_y / magnitude;
			m_z = m_z / magnitude;

			return *this;
		}

		vec3 vec3::Cross(vec3 const& other) const
		{
			return vec3{ m_y * other.m_z - m_z * other.m_y,
						-(m_x * other.m_z - m_z * other.m_x),
						m_x * other.m_y - m_y * other.m_x };
		}

		float vec3::Dot(vec3 const& other) const
		{
			return m_x * other.m_x + m_y * other.m_y + m_z * other.m_z;
		}

		float& vec3::operator[](size_t index)
		{
			switch (index)
			{
			case 0:
				return m_x;
			case 1:
				return m_y;
			case 2:
				return m_z;
			default:
				assert(false); // kill function; // TODO: remove ref (ref = 8 octets / float = 4)
				return m_x; // return first value to remove warning
			}
		}

		float vec3::operator[](size_t index) const
		{
			switch (index)
			{
			case 0:
				return m_x;
			case 1:
				return m_y;
			case 2:
				return m_z;
			default:
				assert(false); // kill function;
				return 0; // return 0 to remove warning
			}
		}

		vec3 vec3::operator+(vec3 const& vector) const
		{
			vec3 sum{
				this->m_x + vector.m_x,
				this->m_y + vector.m_y,
				this->m_z + vector.m_z,
			};
			return sum;
		}

		vec3& vec3::operator+=(vec3 const& other)
		{
			this->m_x += other.m_x;
			this->m_y += other.m_y;
			this->m_z += other.m_z;
			return *this;
		}

		vec3& vec3::operator-=(vec3 const& other)
		{
			this->m_x -= other.m_x;
			this->m_y -= other.m_y;
			this->m_z -= other.m_z;
			return *this;
		}

		vec3& vec3::operator=(vec4 const& vec)
		{
			this->m_x = vec.m_x;
			this->m_y = vec.m_y;
			this->m_z = vec.m_z;
			return *this;
		}

		vec3 vec3::operator*(vec3 const& other)
		{
			return { m_x * other.m_x, m_y * other.m_y, m_z * other.m_z };
		}

		vec3 vec3::operator-() const
		{
			return { -m_x, -m_y, -m_z };
		}

		vec3 vec3::operator-(vec3 const& other) const
		{
			vec3 difference{
				this->m_x - other.m_x,
				this->m_y - other.m_y,
				this->m_z - other.m_z
			};
			return difference;
		}

		vec3 vec3::operator*(float scalar) const
		{
			vec3 product{
				this->m_x * scalar,
				this->m_y * scalar,
				this->m_z * scalar,
			};
			return product;
		}

		vec3& vec3::operator*=(float scalar)
		{
			this->m_x *= scalar;
			this->m_y *= scalar;
			this->m_z *= scalar;

			return *this;
		}

		vec3 vec3::operator*(Core::Maths::mat4 const& matrix)
		{
			float x = this->m_x * matrix[0][0] + this->m_y * matrix[0][1] + this->m_z * matrix[0][2] + 1.f * matrix[0][3];
			float y = this->m_x * matrix[1][0] + this->m_y * matrix[1][1] + this->m_z * matrix[1][2] + 1.f * matrix[1][3];
			float z = this->m_x * matrix[2][0] + this->m_y * matrix[2][1] + this->m_z * matrix[2][2] + 1.f * matrix[2][3];
			return vec3(x, y, z);
		}
	}
}