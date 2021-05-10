#include "Resources/Mesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

namespace Resources
{
	Mesh::Mesh(const char* path)
	{
		LoadModel(path);
	}

	Mesh::Mesh(std::initializer_list<float> data) :
		m_data(data)
	{
	}

	Mesh::Mesh(const std::vector<float>& data):
		m_data(data)
	{
	}

	void Mesh::LoadModel(std::string path)
	{
		//https://en.wikipedia.org/wiki/Wavefront_.obj_file
		std::string currentLine;
		std::ifstream objFile(path);

		if (!objFile.is_open())
		{
			std::cerr << "Error opening file : " << path << std::endl;
			return;
		}

		while (getline(objFile, currentLine))
		{
			currentLine.erase(currentLine.find_last_not_of(" ") + 1);
			std::istringstream stream(currentLine);

			std::string lineType;
			stream >> lineType;

			if (lineType == "v")
			{
				float x, y, z, w;
				stream >> x;
				stream >> y;
				stream >> z;

				if (!stream.eof())
				{
					stream >> w;
					if (w != 1.0f)
					{
						w = 1 / w;
						x *= w;
						y *= w;
						z *= w;
					}
				}
				m_position.push_back({ x, y, z });
				continue;
			}

			if (lineType == "vn")
			{
				float x, y, z;
				stream >> x;
				stream >> y;
				stream >> z;

				m_normal.push_back({ x, y, z });
				continue;
			}

			if (lineType == "vt")
			{
				float u, v, w;
				stream >> u;

				if (!stream.eof())
				{
					stream >> v;
				}
				else
				{
					v = 0;
				}

				if (!stream.eof())
				{
					stream >> w;
				}
				else
				{
					w = 0;
				}

				m_textCoord.push_back({ u, v });
				continue;
			}

			if (lineType == "f")
			{
				std::string vertex1, vertex2, vertex3;

				stream >> vertex1;
				Parse(vertex1);

				stream >> vertex2;
				Parse(vertex2);

				stream >> vertex3;
				Parse(vertex3);

				while (!stream.eof())
				{
					vertex2 = vertex3;
					stream >> vertex3;

					Parse(vertex1);
					Parse(vertex2);
					Parse(vertex3);
				}

				continue;
			}	
		}
		std::vector<Core::Maths::vec3>().swap(m_position);
		std::vector<Core::Maths::vec3>().swap(m_normal);
		std::vector<Core::Maths::vec2>().swap(m_textCoord);
	}

	void Mesh::Parse(std::string const& string)
	{
		unsigned int intIndex;
		std::istringstream stream(string);
		std::string strIndex;

		if (getline(stream, strIndex, '/'))
		{
			intIndex = ParseIndex(strIndex, m_position);
			m_data.push_back(m_position[intIndex].m_x);
			m_data.push_back(m_position[intIndex].m_y);
			m_data.push_back(m_position[intIndex].m_z);

			m_data.push_back(1.f);
			m_data.push_back(1.f);
			m_data.push_back(1.f);

			if (getline(stream, strIndex, '/'))
			{
				std::string strTexel = strIndex;
				if (getline(stream, strIndex, '/'))
				{
					intIndex = ParseIndex(strIndex, m_normal);
					m_data.push_back(m_normal[intIndex].m_x);
					m_data.push_back(m_normal[intIndex].m_y);
					m_data.push_back(m_normal[intIndex].m_z);
				}
				else
				{
					m_data.push_back(1.f);
					m_data.push_back(1.f);
					m_data.push_back(1.f);
				}

				if (!strTexel.empty())
				{
					intIndex = ParseIndex(strTexel, m_textCoord);
					m_data.push_back(m_textCoord[intIndex].m_s);
					m_data.push_back(m_textCoord[intIndex].m_t);
				}
				else
				{
					m_data.push_back(1.f);
					m_data.push_back(1.f);
				}
			}
			else
			{
				m_data.push_back(1.f);
				m_data.push_back(1.f);
				m_data.push_back(1.f);
				m_data.push_back(1.f);
				m_data.push_back(1.f);
			}
		}
	}

	void Mesh::SetData(const std::vector<float>& data)
	{
		m_data = data;
	}

	Mesh Mesh::CreateCube()
	{
								/*CUBE*/
		//---------------------------------------------------------------------
		return {
			/*Position*/			/*Color*/			/*Normal*/			/*Texel*/

		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,		1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,		1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,		0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, -1.0f,		1.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,		1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,		1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 0.0f, 1.0f,		0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  -1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
////
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,		1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,		1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,		0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  1.0f, 0.0f, 0.0f,		0.0f, 1.0f,
////
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f,		0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f,		1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f,		1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f,		0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, -1.0f, 0.0f,		0.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,		1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,		0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,		0.0f, 1.0f,
		- 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,		0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,	1.0f, 1.0f, 1.0f,  0.0f, 1.0f, 0.0f,		1.0f, 0.0f
		};
	}

	Mesh Mesh::CreateTriangle()
	{
									/*Triangle*/
		//-----------------------------------------------------------------------
		return {
			//Position				//Color					//texCoord
			 0.f, 0.5f, 0.0f,		1.f, 0.f, 0.f,			0.5f, 1.f,//top midle
			 -0.5f, -0.5f, 0.0f,	0.f, 1.f, 0.f,			0.f, 0.f,//bottom left
			 0.5f, -0.5f, 0.0f,		0.f, 0.f, 1.f,			1.f, 0.f//bottom right
		};
	}

	Mesh Mesh::CreateSquare()
	{
								/*Square*/
		//-----------------------------------------------------------------------
		return{
			// Position				//Color				//TextCoord
			 0.5f,  0.5f, 0.0f,		1.f, 0.f, 0.f,		 1.f, 1.f,// top right
			 0.5f, -0.5f, 0.0f,		0.f, 1.f, 0.f,		 1.f, 0.f,// bottom right
			-0.5f,  -0.5f, 0.0f,	0.f, 0.f, 1.f,		 0.f, 0.f,// bottom left
			-0.5f,  0.5f, 0.0f,		0.f, 0.f, 1.f,		 0.f, 1.f// top left
		};
	}

	
}