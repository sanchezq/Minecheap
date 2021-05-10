#pragma once
#include "LowRenderer/Model.h"
namespace Resources
{
	// Parser OBJ
	class lib_API Mesh
	{
	public:
		Mesh() = default;
		Mesh(const char* path);
		Mesh(std::initializer_list<float> data);
		Mesh(const std::vector<float>& data);
		~Mesh() = default;

		inline const std::vector<float>& GetData() const { return m_data; }
		static Mesh CreateCube();
		static Mesh CreateTriangle();
		static Mesh CreateSquare();

		void Parse(std::string const& string);

		void  SetData(const std::vector<float>& data);

	private:
		void LoadModel(std::string path);

#pragma warning(push)
#pragma warning(disable: 4251)
		std::vector<Core::Maths::vec3> m_position;
		std::vector<Core::Maths::vec3> m_normal;
		std::vector<Core::Maths::vec2> m_textCoord;
		std::vector<float> m_data;
#pragma warning(pop)
		template<class T>
		unsigned int ParseIndex(std::string const& strIndex, std::vector<T> const& buffer)
		{
			int intIndex = std::stoi(strIndex) - 1;
			if (intIndex < 0)
			{
				intIndex += (int)buffer.size() + 1;
			}
			return intIndex;
		}
	};
}