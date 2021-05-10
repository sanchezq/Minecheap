#include "Resources/Scene.h"
#include "Maths/mat3.h"
#include "Maths/mat4.h"
#include "glad/glad.h"
#include <iostream>
namespace Resources
{
	Scene::Scene()
	{
		LowRenderer::Camera camera{ Core::Maths::vec3{0.0f, 10.0f, 0.0f} };
		m_camera = camera;
		Resources::Shader ShaderManager{};
		m_shader = ShaderManager;
		m_root = new Graph();
		m_projMatrix = LowRenderer::Camera::CreateProjectionMatrix(m_camera.m_fov, m_width / m_height, 0.1f, m_far);
	}

	Scene::~Scene(void)
	{
		delete m_root;
	}

	void Scene::UpdateScene(float msec)
	{
		UpdateFrustum();
		m_root->Update(msec);
	}

	void Scene::RenderScene()
	{
		/* Render here */
		glClearColor(0.2f, 0.6f, 0.53f, 1.0f);//Color background
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);//Active Depth Buffer
		glUseProgram(m_shader.GetID());

		m_viewMatrix = m_camera.GetViewMatrix();
		DrawNode(*m_root);
	}

	void Scene:: InitScene()
	{
		std::string fragmentShaderText = m_shader.LoadFileGLSL("resources/Shaders/ShaderFrag.frag");
		std::string vertexShaderText = m_shader.LoadFileGLSL("resources/Shaders/ShaderVertex.vert");
		m_shader.CreateShaderProgram(fragmentShaderText.c_str(), vertexShaderText.c_str());
	}

	Core::DataStructure::Graph* Scene::GetRoot()
	{
		return m_root;
	}

	void Scene::UpdateProjectionMatrix()
	{
		m_projMatrix = LowRenderer::Camera::CreateProjectionMatrix(m_camera.m_fov, m_width / m_height, 0.1f, m_far);
	}

	const Core::Maths::mat4& Scene::GetProjectionMatrix() const
	{
		return m_projMatrix;
	}

	const Core::Maths::mat4& Scene::GetViewMatrix() const
	{
		return m_viewMatrix;
	}

	void Scene::UpdateFrustum()
	{
		const float horizFov = m_camera.m_fov * m_width / m_height,
					horizLeftLineAngle = m_camera.m_yaw + horizFov * .5f,
					horizLeftPlaneAngle = horizLeftLineAngle - 90.f,
					horizRightLineAngle = horizLeftLineAngle - horizFov,
					horizRightPlaneAngle = horizRightLineAngle + 90.f,
					horizFarPlaneAngle = m_camera.m_yaw + 180.f,
					horizFarLineAngle = m_camera.m_yaw + 90.f;

		float toRad = (float)M_PI / 180.f;

		m_leftPlaneVec = vec3{ cosf(horizLeftPlaneAngle * toRad), 0.f, sinf(horizLeftPlaneAngle * toRad) };
		m_rightPlaneVec = vec3{ cosf(horizRightPlaneAngle * toRad), 0.f, sinf(horizRightPlaneAngle * toRad) };
		m_farPlaneVec = vec3{ cosf(horizFarPlaneAngle * toRad), 0.f, sinf(horizFarPlaneAngle * toRad) };

		const vec3	leftLineVec{ cosf(horizLeftLineAngle * toRad), 0.f, sinf(horizLeftLineAngle * toRad) },
					rightLineVec{ cosf(horizRightLineAngle * toRad), 0.f, sinf(horizRightLineAngle * toRad) },
					farLineVec{ cosf(horizFarLineAngle * toRad), 0.f, sinf(horizFarLineAngle * toRad) },
					farPoint{ m_camera.m_cameraPos.m_x - m_far * m_farPlaneVec.m_x, 0.f, m_camera.m_cameraPos.m_z - m_far * m_farPlaneVec.m_z };

		m_leftDist = leftLineVec.m_x * m_camera.m_cameraPos.m_z - leftLineVec.m_z * m_camera.m_cameraPos.m_x;
		m_rightDist = rightLineVec.m_x * m_camera.m_cameraPos.m_z - rightLineVec.m_z * m_camera.m_cameraPos.m_x;
		m_farDist = farLineVec.m_x * farPoint.m_z - farLineVec.m_z * farPoint.m_x;
	}

	bool Scene::IsInFrustum(const vec3& center, const float radius) const
	{
		const bool	isInsideLeft = center.m_x * m_leftPlaneVec.m_x + center.m_z * m_leftPlaneVec.m_z + m_leftDist + radius > 0.f,
					isInsideRight = center.m_x * m_rightPlaneVec.m_x + center.m_z * m_rightPlaneVec.m_z - m_rightDist + radius > 0.f,
					isInsideFar = center.m_x * m_farPlaneVec.m_x + center.m_z * m_farPlaneVec.m_z - m_farDist + radius > 0.f;

		return isInsideLeft && isInsideRight && isInsideFar;
	}

	void Scene::CalculateViewPort(const float height, const float width)
	{
		m_height = height;
		m_width = width;
		glViewport(0, 0, (GLsizei)width, (GLsizei)height);
	}

	void Scene::DrawNode(Graph& node)
	{
		if (node.GetModel())
		{
			if(!IsInFrustum(node.GetWorldCenter(), node.GetRadius()))
			{
				return;
			}

			//printf("[]  ");

			/*MATRIX*/
			//----------------------------------------------------------------------------------------------
			mat4 model = mat4::Identity();
			model = Resources::Transform::Scale(node.GetWorldTransform(), node.GetModelScale());

			Core::Maths::mat4 MVP = m_projMatrix * m_viewMatrix * model;
			GLuint programID = m_shader.GetID();
			GLint Loc = glGetUniformLocation(programID, "MVP");
			glUniformMatrix4fv(Loc, 1, GL_TRUE, MVP.m_matrix);

			/*Normal Matrix*/
			Loc = glGetUniformLocation(programID, "model");
			glUniformMatrix4fv(Loc, 1, GL_TRUE, model.m_matrix);

			Core::Maths::mat3 normal = Resources::Transform::NormalMatrix(model);
			Loc = glGetUniformLocation(programID, "normalMatrix");
			glUniformMatrix3fv(Loc, 1, GL_TRUE, normal.m_matrix);

			m_shader.SetVec3(m_camera.m_cameraPos, "viewPos", m_shader.GetID());

			//----------------------------------------------------------------------------------------------

			node.Draw();
		}
		for (auto
			i = node.GetChildIteratorStart();
			i != node.GetChildIteratorEnd(); ++i)
		{
			DrawNode(*(*i));
		}

	}
}