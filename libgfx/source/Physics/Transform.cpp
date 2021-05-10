#include "Physics/Transform.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace Resources
{
	Core::Maths::mat4 Transform::CreateTranslateMatrix(const vec3& vec3)
	{
		return { 1.f,	0.f,	0.f,	vec3.m_x,
				 0.f,	1.f,	0.f,	vec3.m_y,
				 0.f,	0.f,	1.f,	vec3.m_z,
				 0.f,	0.f,	0.f,	1.f };
	}

	Core::Maths::mat4 Transform::Translate(const mat4 matrix, const vec3& vec3)
	{
		return  matrix * Transform::CreateTranslateMatrix(vec3);
	}

	Core::Maths::mat4 Transform::CreateScaleMatrix(const vec3& vec3)
	{
		return { vec3.m_x,		0.f,		0.f,	0.f,
					0.f,		vec3.m_y,		0.f,	0.f,
					0.f,			0.f,	vec3.m_z,	0.f,
					0.f,			0.f,		0.f,	1.f };
	}

	Core::Maths::mat4 Transform::Scale(const mat4 matrix, const vec3& vec3)
	{
		return matrix * CreateScaleMatrix(vec3);
	}

	Core::Maths::mat4 Transform::CreateRotateMatrix(float angle, const vec3& vec3)
	{
		angle *= (float)(M_PI / 180);
		/*Representation of the Matrix*/
		/*
				a,	b,	c,	d,
				e,	f,	g,	h,
				i,	j,	k,	l,
				m,	n,	o,	p
		*/
		/*the matrix below and the fusion of the three rotation matrix*/

		float a = cosf(angle) + (vec3.m_x * vec3.m_x) * (1 - cosf(angle));
		float b = vec3.m_x * vec3.m_y * (1 - cosf(angle)) - vec3.m_z * sinf(angle);
		float c = vec3.m_x * vec3.m_z * (1 - cosf(angle)) + vec3.m_y * sinf(angle);
		float e = vec3.m_y * vec3.m_x * (1 - cosf(angle)) + vec3.m_z * sinf(angle);
		float f = cosf(angle) + (vec3.m_y * vec3.m_y) * (1 - cosf(angle));
		float g = vec3.m_y * vec3.m_z * (1 - cosf(angle)) - vec3.m_x * sinf(angle);
		float i = vec3.m_z * vec3.m_x * (1 - cosf(angle)) - vec3.m_y * sinf(angle);
		float j = vec3.m_z * vec3.m_y * (1 - cosf(angle)) + vec3.m_x * sinf(angle);
		float k = cosf(angle) + (vec3.m_z * vec3.m_z) * (1 - cosf(angle));

		return{ a,		b,		c,		0.f,
				e,		f,		g,		0.f,
				i,		j,		k,		0.f,
				0.f,	0.f,	0.f,	1.f
		};
	}

	Core::Maths::mat4 Transform::Rotate(const mat4 matrix, float angle, const vec3& vec3)
	{
		return matrix * CreateRotateMatrix(angle, vec3);
	}

	Core::Maths::mat4 Transform::LookAt(const vec3& cameraPosition, const vec3& cameraTarget, const vec3& upVector)
	{
		Core::Maths::vec3 cameraDirection = (cameraPosition - cameraTarget).Normalize();
		Core::Maths::vec3 cameraRight = upVector.Cross(cameraDirection).Normalize();//X
		Core::Maths::vec3 cameraUp = cameraDirection.Cross(cameraRight).Normalize();//Y

		Core::Maths::mat4 view{ cameraRight.m_x,	cameraRight.m_y,	cameraRight.m_z,	 0.f,
								cameraUp.m_x,		cameraUp.m_y,		 cameraUp.m_z,		0.f,
								cameraDirection.m_x, cameraDirection.m_y, cameraDirection.m_z,	0.f,
									0.f,				0.f,					0.f,			1.f };

		Core::Maths::mat4 pos{ 1.f, 0.f, 0.f,  -cameraPosition.m_x,
								0.f, 1.f, 0.f, -cameraPosition.m_y,
								0.f, 0.f, 1.f, -cameraPosition.m_z,
								0.f, 0.f, 0.f,			1.f
		};

		return view * pos;
	}

	Core::Maths::mat3 Transform::NormalMatrix(const mat4 modelMatrix)
	{
		mat3 model = mat3{ modelMatrix };
		float determinant = mat3::GetDeterminant(model);
		float factor = 1 / determinant;
		model = mat3::TransposeMatrix(model);

		/*minor determinant*/
		float a = (model[1][1] * model[2][2] - model[1][2] * model[2][1]);
		float b = -(model[1][0] * model[2][2] - model[1][2] * model[2][0]);
		float c = (model[1][1] * model[2][1] - model[1][1] * model[2][0]);

		float d = -(model[0][1] * model[2][2] - model[0][2] * model[2][1]);
		float e = (model[0][0] * model[2][2] - model[0][2] * model[2][0]);
		float f = -(model[0][0] * model[2][1] - model[0][1] * model[2][0]);

		float g = (model[0][1] * model[1][2] - model[0][2] * model[1][1]);
		float h = -(model[0][0] * model[1][2] - model[0][2] * model[1][0]);
		float i = (model[0][0] * model[1][1] - model[0][1] * model[1][0]);
		



		return {a * factor, b * factor, c * factor,
				d * factor, e * factor, f * factor,
				g * factor, h * factor, i * factor};
	}
}