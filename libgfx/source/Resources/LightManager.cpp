#include "Resources/LightManager.h"
#include <string>
#include <iostream>
namespace LowRenderer
{
	LightManager LightManager::m_instance;
	void LightManager::DirectionalLight(vec3 const& direction, vec3 const& ambient, vec3 const& diffuse, vec3 const& specular)
	{
		vec4 pos{ direction.m_x, direction.m_y, direction.m_z, 0.f};
		m_instance.m_lights.push_back(Light(pos, ambient, diffuse, specular));
	}

	void LightManager::SpotLight(vec3 const& position, vec3 const& ambient, vec3 const& diffuse, vec3 const& specular)
	{
		vec4 pos{ position.m_x, position.m_y, position.m_z, 1.f };
		m_instance.m_lights.push_back(Light(pos, ambient, diffuse, specular));
	}

	void LightManager::PointLight(vec3 const& position, vec3 const& ambient, vec3 const& diffuse, vec3 const& specular)
	{
		vec4 pos{ position.m_x, position.m_y, position.m_z, 1.f };
		Light light = Light(pos, ambient, diffuse, specular);
		light.SetPointLight();
		m_instance.m_lights.push_back(light);
	}

	Light* LightManager::GetLight(unsigned int index)
	{
		if (index >= m_instance.m_lights.size())
		{
			std::cerr << "no have light in this index" << std::endl;
			return nullptr;
		}
		return &m_instance.m_lights[index];
	}

	void LightManager::SetLight(Light& light, int index)
	{
		if (index >= m_instance.m_lights.size())
		{
			std::cerr << "no have light in this index" << std::endl;
			return;
		}
		m_instance.m_lights[index] = light;
	}

	void LightManager::UpdateShader(GLuint const& programID)
	{
		for (size_t i = 0; i < m_instance.m_lights.size(); i++)
		{
			std::string path = "light[" + std::to_string(i) + "].specular";
			m_instance.m_shader->SetVec3(m_instance.m_lights[i].m_specular, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].position";
			m_instance.m_shader->SetVec4(m_instance.m_lights[i].m_position, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].direction";
			m_instance.m_shader->SetVec3(m_instance.m_lights[i].m_direction, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].constant";
			m_instance.m_shader->SetFloat(m_instance.m_lights[i].m_constant, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].innerCone";
			m_instance.m_shader->SetFloat(m_instance.m_lights[i].m_innerCone, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].outerCone";
			m_instance.m_shader->SetFloat(m_instance.m_lights[i].m_outerCone, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].linear";
			m_instance.m_shader->SetFloat(m_instance.m_lights[i].m_linear, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].quadratic";
			m_instance.m_shader->SetFloat(m_instance.m_lights[i].m_quadratic, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].ambient";
			m_instance.m_shader->SetVec3(m_instance.m_lights[i].m_ambientColor, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].diffuse";
			m_instance.m_shader->SetVec3(m_instance.m_lights[i].m_diffuseColor, path.c_str(), programID);

			path = "light[" + std::to_string(i) + "].is_point";
			m_instance.m_shader->SetBool(m_instance.m_lights[i].m_isPoint, path.c_str(), programID);
		}
		m_instance.m_shader->SetInt((int)m_instance.m_lights.size(), "nbrLight", programID);
	}
}