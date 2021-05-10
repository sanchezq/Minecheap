#include "Resources/Shader.h"
#include <iostream>

void Resources::Shader::CreateShaderProgram(const GLchar* fragmentShaderSource, const GLchar* vertexShaderSource)
{
	//creation of a vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	glCompileShader(vertexShader);

	//Check for shader compile errors
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//creation of a fragment shader
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	//Check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	//link shaders
	//creation of a program object
	unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	//Check for program compile errors
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::PROGRAM::LINKER_FAILED\n" << infoLog << std::endl;
	}

	//delete shader objects once we have linked them to the program object
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	m_ID = shaderProgram;
}

std::string Resources::Shader::LoadFileGLSL(const std::string filePath)
{
	std::ifstream file(filePath);
	std::stringstream sstream;

	if (!file.is_open())
	{
		std::cerr << "not find the file: " << filePath << std::endl;
	}

	sstream << file.rdbuf();

	return sstream.str();
}

void Resources::Shader::SetFloat(float value, const GLchar* name, GLuint program)
{
	GLint addFloat = glGetUniformLocation(program, name);
	glProgramUniform1f(program, addFloat, value);
}

void Resources::Shader::SetInt(int value, const GLchar* name, GLuint program)
{
	GLint addInt = glGetUniformLocation(program, name);
	glProgramUniform1i(program, addInt, value);
}

void Resources::Shader::SetBool(bool value, const GLchar* name, GLuint program)
{
	GLint addBool = glGetUniformLocation(program, name);
	glProgramUniform1i(program, addBool,value);
}

void Resources::Shader::SetVec3(vec3 vector, const GLchar* name, GLuint program)
{
	GLint addVec3 = glGetUniformLocation(program, name);
	glProgramUniform3f(program, addVec3, vector.m_x, vector.m_y, vector.m_z);
}

void Resources::Shader::SetVec4(vec4 vector, const GLchar* name, GLuint program)
{

	GLint addVec4 = glGetUniformLocation(program, name);
	glProgramUniform4f(program, addVec4, vector.m_x, vector.m_y, vector.m_z, vector.m_w);
}

void Resources::Shader::SetMat4(mat4 matrix, const GLchar* name, GLuint program)
{
	GLint addMat4 = glGetUniformLocation(program, name);
	glProgramUniformMatrix4fv(program, addMat4, 1, GL_TRUE, matrix.m_matrix);//TRUE because this program is row-major
}

unsigned int Resources::Shader::GetID()
{
	return m_ID;
}
