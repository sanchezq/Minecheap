#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Maths/mat3.h"
#include "Maths/vec3.h"
#include "Maths/vec4.h"
namespace Resources
{
	// Unity
	class lib_API Transform
	{
	public:
		using mat4 = Core::Maths::mat4;
		using mat3 = Core::Maths::mat3;
		using vec3 = Core::Maths::vec3;
		Transform() = delete;
		~Transform() = default;
		static mat4 CreateTranslateMatrix(const vec3& vec3);
		static mat4 Translate(const mat4 matrix, const vec3& vec3);

		static mat4 CreateScaleMatrix(const vec3& vec3);
		static mat4 Scale(const mat4 matrix, const vec3& vec3);
			   
		static mat4 CreateRotateMatrix(float angle, const vec3& vec3);
		static mat4 Rotate(const mat4 matrix, float angle, const vec3& vec3);
			   
		static mat4 LookAt(const vec3& cameraPosition, const vec3& cameraTarget, const vec3& upVector);
			   
		static mat3 NormalMatrix(const mat4 modelMatrix);
	private:
	};
}