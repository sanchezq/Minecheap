#pragma once
#include "LowRenderer/Light.h"
#include <vector>
#include "Resources/Shader.h"
#include "lib_Export.h"
namespace LowRenderer
{
	class lib_API LightManager
	{
	public:
		using vec3 = Core::Maths::vec3;
		using vec4 = Core::Maths::vec4;

		/*Lights Options*/
		static void DirectionalLight(vec3 const& direction, vec3 const& ambient, vec3 const& diffuse, vec3 const& specular);
		static void SpotLight(vec3 const& position, vec3 const& ambient, vec3 const& diffuse, vec3 const& specular);
		static void PointLight(vec3 const& position, vec3 const& ambient, vec3 const& diffuse, vec3 const& specular);

		static Light* GetLight(unsigned int index);
		static void SetLight(Light& light, int index);

		/*Update values in Shader*/
		 static void UpdateShader(GLuint const& programID);
	private:
		/*Singleton*/
		LightManager() = default;
		~LightManager() = default;
		static LightManager m_instance;
#pragma warning(push)
#pragma warning(disable: 4251)
		std::vector<Light> m_lights;
#pragma warning(pop)
		Resources::Shader* m_shader{};
	};
}