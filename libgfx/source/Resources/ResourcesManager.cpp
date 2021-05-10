#include "Resources/ResourcesManager.h"

namespace Resources
{
	ResourcesManager ResourcesManager::m_instance;
	unsigned int ResourcesManager::GetTexture(std::string path,const bool invert)
	{
		return m_instance.m_texManager.GetTextureID(path, invert);
	}
}