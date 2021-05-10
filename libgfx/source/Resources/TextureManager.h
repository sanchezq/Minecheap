#pragma once
#include <map>
#include <string>
#include "lib_Export.h"
namespace Resources
{
	class lib_API TextureManager
	{
	public:
		TextureManager() = default;
		~TextureManager() = default;

		unsigned int GetTextureID(std::string& path, bool invert = true);

	private:
#pragma warning(push)
#pragma warning(disable: 4251)
		std::map<std::string, unsigned int> m_textureMap;
#pragma warning(pop)
	};

}