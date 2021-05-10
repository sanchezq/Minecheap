#include "LowRenderer/Light.h"
#define _USE_MATH_DEFINES
#include <math.h>

namespace LowRenderer
{
	Light::Light(float x, float y, float z, float w, float ambient, float diffuse, float specular):
		m_position(x, y, z, w),
		m_ambientColor(ambient, ambient, ambient),
		m_diffuseColor(diffuse, diffuse, diffuse),
		m_specular(specular, specular, specular)
	{
	}

	Light::Light(vec4 position, vec3 ambient, vec3 diffuse, vec3 specular):
		m_position(position),
		m_ambientColor(ambient),
		m_diffuseColor(diffuse),
		m_specular(specular)
	{
	}

	void Light::SetDiffuseColor(vec3 const& color)
	{
		m_diffuseColor = color;
	}

	void Light::SetAmbientColor(vec3 const& color)
	{
		m_ambientColor = color;
	}

	void Light::SetSpecular(vec3 const& specular)
	{
		m_specular = specular;
	}

	void Light::SetDirection(vec3 const& direction)
	{
		m_direction = direction;
	}

	void Light::SetPosition(vec4 const& position)
	{
		m_position = position;
	}

	void Light::SetAttenuation(float const& linear, float const& quadratic)
	{
		m_linear = linear;
		m_quadratic = quadratic;
	}

	void Light::SetCutOff(float const& innerCone, float const& outerCone)
	{
		m_innerCone = cosf(innerCone * (float)(M_PI / 180));
		m_outerCone = cosf(outerCone * (float)(M_PI / 180));
	}

	void Light::SetPointLight()
	{
		m_isPoint = true;
	}
}