#pragma once
#include "Maths/mat4.h"
#include "Maths/vec4.h"
#include "Resources/Mesh.h"
#include <vector>
namespace Core
{
	namespace DataStructure
	{
		class lib_API Graph
		{
		public:
			using vec4 = Core::Maths::vec4;
			using vec3 = Core::Maths::vec3;
			using mat4 = Core::Maths::mat4;
			Graph(LowRenderer::Model* model = nullptr, float radius = 0.f, vec3 localCenter = Core::Maths::vec3{ 0.f, 0.f, 0.f }, Core::Maths::vec4 color = Core::Maths::vec4{ 1.f, 1.f, 1.f, 1.f });
			~Graph();
			void SetTransform(const mat4& matrix) { m_transform = matrix; }
			const mat4& GetTransform() const { return m_transform; }
			mat4 GetWorldTransform() const { return m_worldTransform; }
			vec3 GetWorldPosition() const { return { m_worldTransform[0][3], m_worldTransform[1][3], m_worldTransform[2][3] }; }
			vec3 GetWorldCenter() const { return m_localCenter + vec3{ m_worldTransform[0][3], m_worldTransform[1][3], m_worldTransform[2][3] }; }

			float GetRadius() const { return m_radius; }

			Core::Maths::vec4 GetColor() const { return m_color; }
			void SetColor(Core::Maths::vec4 color) { m_color = color; }

			vec3 GetModelScale() const { return m_modelScale; }
			void SetModelScale(vec3 scale) { m_modelScale = scale; }

			LowRenderer::Model* GetModel() const { return m_model; }
			void SetModel(LowRenderer::Model* model) { m_model = model; }

			void AddChild(Graph* scene);

			virtual void Update(float msec);
			virtual void Draw();
			std::vector <Graph*>::iterator GetChildIteratorStart() {
				return m_children.begin();
			}

			std::vector <Graph*>::iterator GetChildIteratorEnd() {
				return m_children.end();
			}

			float m_angle = 0.f;

		protected:
			Graph* m_parent = nullptr;
			float m_radius = 0.f;
			vec3 m_localCenter{ 0.f, 0.f, 0.f };
			LowRenderer::Model* m_model;
			mat4 m_worldTransform = mat4::Identity();
			mat4 m_transform = mat4::Identity();
			vec3 m_modelScale{ 1.f, 1.f, 1.f };
			Core::Maths::vec4 m_color{ 1.f,1.f,1.f };
#pragma warning(push)
#pragma warning(disable: 4251)
			std::vector<Graph*> m_children;
#pragma warning(pop)
		};

	}
}
