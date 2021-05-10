#pragma once
#include <string>
#include "TextureManager.h"
#include "lib_Export.h"
namespace Resources
{
	class ResourcesManager
	{
	public:
		lib_API static unsigned int GetTexture(std::string path, bool invert = true);
		

	private:
		/*Singleton*/
		ResourcesManager() = default;
		~ResourcesManager() = default;
		static ResourcesManager m_instance;

		TextureManager m_texManager;
	};

}