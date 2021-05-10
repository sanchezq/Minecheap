#pragma once

#include "Maths/vec3.h"
#include "Maths/vec4.h"
#include <glad/glad.h>

namespace LowRenderer
{
	class lib_API Light
	{
	public:
		//TODO move dir spot and point in light manager// Add function add light
		using vec3 = Core::Maths::vec3;
		using vec4 = Core::Maths::vec4; 
		Light(float x, float y, float z, float w, float ambientColor, float diffuseColor, float specular);
		Light(vec4 position, vec3 ambientColor, vec3 diffuseColor, vec3 specular);
		~Light() = default;


		/*Color Light*/
		void SetDiffuseColor(vec3 const& color);
		void SetAmbientColor(vec3 const& color);

		/*Light Settings*/
		void SetSpecular(vec3 const& specular);
		void SetDirection(vec3 const& direction);
		void SetPosition(vec4 const& position);

		void SetAttenuation(float const& linear = 0.09f, float const& quadratic = 0.32f);
		void SetCutOff(float const& innerCone, float const& outerCone);
		
		void SetPointLight();

		/*Color*/
		vec3 m_diffuseColor{ 0.5f, 0.5f, 0.5f };
		vec3 m_ambientColor{ 0.2f, 0.2f, 0.2f };

		/*Settings*/
		float m_innerCone = 12.5f;
		float m_outerCone = 17.5f;
		vec3 m_direction{1.f, 1.f, 1.f};
		vec3 m_specular{ 1.f, 1.f, 1.f };
		vec4 m_position{0.f, 0.f, 0.f};
		float m_constant = 1.f;
		float m_linear = 0.09f;
		//float m_linear = 0.022f;
		//float m_quadratic = 0.0019f;
		bool m_isPoint = false;
		float m_quadratic = 0.32f;
	};
}