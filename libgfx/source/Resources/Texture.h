#pragma once
#include "lib_Export.h"
namespace Resources
{
	struct lib_API TemporaryTexture
	{
		unsigned char* m_pixels;
		TemporaryTexture(const char* filename, int* width, int* height, int* comp, int req_comp);
		~TemporaryTexture();
	};
	class Texture
	{
	public:
		Texture(const char* filename, bool invert = true);
		~Texture() = default;
		unsigned int GetID() const;
	private:
		unsigned int m_ID = 0;
		
	};
}