#pragma once
#include "Physics/Transform.h"
#include "lib_Export.h"
namespace LowRenderer
{
	//TODO
	const float g_yaw = -90.f;
	const float g_pitch = 0.f;
	const float g_speed = 3.f;
	const float g_sensitivity = 0.02f;
	const float g_zoom = 45.f;
	enum class lib_API MovCamera
	{
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	// Projection Orthographique et Perspective
	class lib_API Camera
	{
	public:
		using vec3 = Core::Maths::vec3;
		using mat4 = Core::Maths::mat4;

		Camera(vec3 position = vec3{ 0.f, 0.f, 0.f }, vec3 front = vec3{ 0.f, 0.f, -1.f }, vec3 up = vec3{ 0.f, 1.f, 0.f }, float yaw = g_yaw, float pitch = g_pitch);
		~Camera() = default;

		static mat4 CreateOrthographicMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far);
		static mat4 CreateProjectionMatrix(float fov, const float aspectRatio, const float near, const float far);

		//Euler Angles
		float m_yaw;
		float m_pitch;

		float m_movementSpeed;
		float m_sensitivity;
		float m_zoom;
		float m_fov = 90.f;

		vec3 m_cameraPos{ 0.0f, 0.0f, 3.0f };
		vec3 m_cameraFront{ 0.0f, 0.0f, -1.0f };
		vec3 m_cameraUp{ 0.0f, 1.0f, 0.0f };
		vec3 m_cameraRight{ 0.f, 0.f, 1.f };
		vec3 m_worldUp{ 0.f, 1.f, 0.f };

		mat4 GetViewMatrix();
		void MoveCamera(MovCamera direction, float deltaTime);
		void MouseMoveCamera(float xOffset, float yOffset, bool contrainHeight = true);

		void SetIsLookingAt(bool isLookingAt);
		void SetTarget(vec3 target);

	private:
		void UpdateVectors();

		bool m_isLookingAt = false;
		vec3 m_targetPos{ 0.0f, 0.0f, 0.0f };
		float m_radius = 8.5f;
		float m_camAngleX = 0;
		float m_camAngleZ = 0;
		float m_camAngleY = 0;

	};
}