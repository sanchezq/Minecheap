#include "Resources/Mesh.h"
#include <glad/glad.h>
#include <cstddef> //offsetof
#include <iostream>
namespace LowRenderer
{

	Model::Model(std::vector<float>const& data)
	{
		SetupModel(data);
		SetupScaleBox();
	}

	void Model::Draw()
	{
		if (m_data.size() == NULL)
		{
			std::cerr << "data NULL in Draw(Model)" << std::endl;
			return;
		}
		//verify textures
		/*unsigned int diffuseNr = 1;
		unsigned int specularNr = 1;
		unsigned int normalNr = 1;
		unsigned int heightNr = 1;*/
		//TODO
		//for (unsigned int i = 0; i < m_textures.size(); i++)
		//{
		//	glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
		//	// retrieve texture number (the N in diffuse_textureN)
		//	std::string number;
		//	std::string name = m_textures[i].textType;
		//	if (name == "texture_diffuse")
		//		number = std::to_string(diffuseNr++);
		//	else if (name == "texture_specular")
		//		number = std::to_string(specularNr++); // transfer unsigned int to stream
		//	else if (name == "texture_normal")
		//		number = std::to_string(normalNr++); // transfer unsigned int to stream
		//	else if (name == "texture_height")
		//		number = std::to_string(heightNr++); // transfer unsigned int to stream

		//	// now set the sampler to the correct texture unit
		//	glUniform1i(glGetUniformLocation(shaderID, (name + number).c_str()), i);
		//	// and finally bind the texture
		//	glBindTexture(GL_TEXTURE_2D, m_textures[i].id);
		//}


		glBindVertexArray(m_VAO);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);

		glBindTextureUnit(0, m_textureID);

		/* Draw in Array */
		//(shape,the starting index of the array,many vertices we want to draw)
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)m_data.size());

		/*Draw in Index*/
		//(shapeMode, number of elements we would like to draw,type of indices, specify an offset in the EBO)
		//glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);
	}

	void Model::SetTextureID(unsigned int const& ID)
	{
		m_textureID = ID;
	}

	Core::Maths::vec3& Model::GetScaleBox()
	{
		return m_scaleBox;
	}

	//Model::~Model()
	//{
	//   glDeleteVertexArrays(1, &m_VAO);
	//   glDeleteBuffers(1, &m_VBO);
	//   glDeleteBuffers(1, &m_EBO);
	//}

	void Model::ModifData(std::vector<float>const& data)
	{


		glNamedBufferData(m_VBO, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
	}

	void Model::SetupModel(std::vector<float>const& data)
	{
		//VBO = Vertex Buffer -> le tout de façon contigüe/all contiguously (position, color, texture coordinate, normal...)
		//VAO = Vertex Array -> contient l’état global courant des buffers bindés/contains the current global state of bound buffers
		//EBO = Element Buffer -> correspond à l’index buffer d’un mesh/corresponds to the index buffer of a mesh

		if (data.size() == NULL)
		{
			std::cerr << "data NULL in SetupModel(Model)" << std::endl;
			return;
		}

		//create a new VAO
		glCreateVertexArrays(1, &m_VAO);
		//create a new VBO
		glCreateBuffers(1, &m_VBO);

		//						(Buffer, Size, Data, Usage)
		glNamedBufferData(m_VBO, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

		//position attribute
		const GLuint positionAttrib = 0;
		glEnableVertexArrayAttrib(m_VAO, positionAttrib); //VAO->index

		glVertexArrayAttribFormat(m_VAO, positionAttrib, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(m_VAO, positionAttrib, 0);

		//color attribute
		const GLuint colorAttrib = 1;
		glEnableVertexArrayAttrib(m_VAO, colorAttrib); //VAO->index

		glVertexArrayAttribFormat(m_VAO, colorAttrib, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
		glVertexArrayAttribBinding(m_VAO, colorAttrib, 0);

		//normal attribute
		const GLuint normalAttrib = 2;
		glEnableVertexArrayAttrib(m_VAO, normalAttrib); //VAO->index

		glVertexArrayAttribFormat(m_VAO, normalAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float));
		glVertexArrayAttribBinding(m_VAO, normalAttrib, 0);

		//texture coord attribute
		const GLuint texAttrib = 3;
		glEnableVertexArrayAttrib(m_VAO, texAttrib); //VAO->index

		glVertexArrayAttribFormat(m_VAO, texAttrib, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float));
		glVertexArrayAttribBinding(m_VAO, texAttrib, 0);

		//vertex buffer -> lier explicitement un VBO à son VAO/explicitly link a VBO to its VAO
		glVertexArrayVertexBuffer(m_VAO, 0, m_VBO, 0, 11 * sizeof(float));

		//index buffer -> lier explicitement un VAO à son EBO/explicitly link a VAO to its EBO
		glVertexArrayElementBuffer(m_VAO, m_EBO);

		for (size_t i = 0; i < data.size();)
		{
			vec3 tempPos{ data[i], data[i + 1], data[i + 2] };
			vec3 tempColor{ data[i + 3], data[i + 4], data[i + 5] };
			vec3 tempNorm{ data[i + 6], data[i + 7], data[i + 8] };
			vec2 tempTexel{ data[i + 9], data[i + 10]};
			i += 11;
			m_data.push_back({ tempPos, tempColor, tempNorm, tempTexel });
		}
	}

	void Model::SetupScaleBox()
	{
		float minX = 0, maxX = 0, minY = 0, maxY = 0, minZ = 0, maxZ = 0;

		for (int i = 0; i < m_data.size(); i++)
		{
			if (i == 0)
			{
				minX = m_data[i].m_position.m_x;
				maxX = m_data[i].m_position.m_x;

				minY = m_data[i].m_position.m_y;
				maxY = m_data[i].m_position.m_y;

				minZ = m_data[i].m_position.m_z;
				maxZ = m_data[i].m_position.m_z;
			}
			else
			{
				if (m_data[i].m_position.m_x < minX) { minX = m_data[i].m_position.m_x; }
				if (m_data[i].m_position.m_x > maxX) { maxX = m_data[i].m_position.m_x; }

				if (m_data[i].m_position.m_y < minY) { minY = m_data[i].m_position.m_y; }
				if (m_data[i].m_position.m_y > maxY) { maxY = m_data[i].m_position.m_y; }

				if (m_data[i].m_position.m_z < minZ) { minZ = m_data[i].m_position.m_z; }
				if (m_data[i].m_position.m_z > maxZ) { maxZ = m_data[i].m_position.m_z; }
			}

			m_scaleBox = Core::Maths::vec3(std::abs(maxX - minX) /2, std::abs(maxY - minY) /2, std::abs(maxZ - minZ) /2);
		}

	}
}