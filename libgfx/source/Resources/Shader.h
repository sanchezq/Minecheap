#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include "Physics/Transform.h"
#include "lib_Export.h"
namespace Resources
{
	// Program
	class lib_API Shader
	{
	public:
		using vec3 = Core::Maths::vec3;
		using vec4 = Core::Maths::vec4;
		using mat4 = Core::Maths::mat4;
		Shader() = default;
		~Shader() = default;

		void CreateShaderProgram(const GLchar* fragmentShaderSource, const GLchar* vertexShaderSource);
		std::string LoadFileGLSL(const std::string filePath);

		void SetFloat(float value, const GLchar* name, GLuint program);
		void Resources::Shader::SetInt(int value, const GLchar* name, GLuint program);
		void SetBool(bool value, const GLchar* name, GLuint program);
		void SetVec3(vec3 vector, const GLchar* name, GLuint program);
		void SetVec4(vec4 vector, const GLchar* name, GLuint program);
		void SetMat4(mat4 matrix, const GLchar* name, GLuint program);
		unsigned int GetID();
	private:
		unsigned int m_ID;
	};
}