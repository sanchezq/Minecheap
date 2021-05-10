#pragma once
#include "Maths/vec3.h"
#include "Maths/vec2.h"
#include <string>
#include <vector>

#include "lib_Export.h"

namespace LowRenderer
{
	class lib_API Model
	{
	public:
		using vec3 = Core::Maths::vec3;
		using vec2 = Core::Maths::vec2;


		struct Vertex
		{
			vec3 m_position;
			vec3 m_color;
			vec3 m_normal;
			vec2 m_texCoord;
			Vertex(float posX, float posY, float posZ, float red, float green, float blue, float normX, float normY, float normZ, float texS, float texT) :
				m_position(posX, posY, posZ),
				m_color(red, green, blue),
				m_normal(normX, normY, normZ),
				m_texCoord(texS, texT)
			{

			};

			Vertex(vec3 const& position, vec3 const& color, vec3 const& normal, vec2 const& texCoord) :
				m_position(position),
				m_color(color),
				m_normal(normal),
				m_texCoord(texCoord)
			{};	
		};
		/*Data for the Model*/
		#pragma warning(push)
		#pragma warning(disable:4251)
		std::vector<Vertex> m_data;
		#pragma warning(pop)


		/*Functions*/
		Model() = default;
		#pragma warning(push)
		#pragma warning(disable:4251)
		Model(std::vector<float> const& data);
		#pragma warning(pop)
		void Draw();
		
		void ModifData(std::vector<float> const& data);
		void SetTextureID(unsigned int const& ID);
		unsigned int GetTextureID()const { return m_textureID; }
		
	/*	~Model() = delete;*/

		vec3& GetScaleBox();
		void SetupModel(std::vector<float>const& data);
	private:

		vec3 m_scaleBox = Core::Maths::vec3(1, 1, 1);

		/*Texture*/
		unsigned int m_textureID = 0;

		/*Render Data*/
		unsigned int m_VAO = 0, m_VBO = 0, m_EBO = 0;
		
		/*Functions*/
		
		void SetupScaleBox();
	};
}