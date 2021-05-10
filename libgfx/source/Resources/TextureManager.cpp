#include "Resources/TextureManager.h"

#include "Resources/Texture.h"
namespace Resources
{
	unsigned int TextureManager::GetTextureID(std::string& path, bool invert)
	{
		std::map<std::string, unsigned int>::iterator it;

		it = m_textureMap.find(path);

		if (it == m_textureMap.end())
		{
			m_textureMap[path] = Texture::Texture(path.c_str(), invert).GetID();
		}

		return m_textureMap[path];
	}
}