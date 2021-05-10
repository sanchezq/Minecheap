#pragma once
#include "LowRenderer/Camera.h"
#include "DataStructure/Graph.h"
#include "Shader.h"
#include "lib_Export.h"
#include  "Maths/mat4.h"
#include "Resources/ResourcesManager.h"

namespace Resources
{
	class lib_API Scene
	{
	public:
		using Graph = Core::DataStructure::Graph;
		using vec4 = Core::Maths::vec4;
		using vec3 = Core::Maths::vec3;
		using mat4 = Core::Maths::mat4;

		Scene();
		virtual~Scene(void);

		virtual void UpdateScene(float msec);
		virtual void RenderScene();

		void InitScene();
		Graph* GetRoot();
		void UpdateProjectionMatrix();
		const mat4& GetProjectionMatrix() const;
		const mat4& GetViewMatrix() const;

		void UpdateFrustum();
		bool IsInFrustum(const vec3& pos, const float radius) const;

		void CalculateViewPort(const float height, const float width);

		LowRenderer::Camera m_camera;
		Shader m_shader;
	private:
		mat4 m_projMatrix;
		mat4 m_viewMatrix;
		void DrawNode(Graph& node);
		float m_width = 1250.f;
		float m_height = 600.f;
		float m_far = 100.0f;
		Graph* m_root = nullptr;

		// Frustum Values
		vec3 m_leftPlaneVec{ 0.f, 0.f, 0.f }, m_rightPlaneVec{ 0.f, 0.f, 0.f }, m_farPlaneVec{ 0.f, 0.f, 0.f};
		float m_leftDist = 0.f, m_rightDist = 0.f, m_farDist = 0.f;
	};

}