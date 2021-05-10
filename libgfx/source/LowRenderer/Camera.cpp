#include "LowRenderer/Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
namespace LowRenderer
{
	Camera::Camera(vec3 position, vec3 front, vec3 up, float yaw, float pitch) : m_movementSpeed(g_speed), m_sensitivity(g_sensitivity), m_zoom(g_zoom)
	{
		m_cameraPos = position;
		m_cameraFront = front;
		m_worldUp = up;
		m_yaw = yaw;
		m_pitch = pitch;
		UpdateVectors();
	}

	Core::Maths::mat4 Camera::CreateOrthographicMatrix(const float left, const float right, const float bottom, const float top, const float near, const float far)
	{
		return { 2 / (right - left),					 0.f,											0.f,					0.f,
					0.f,						 2 / (top - bottom),									0.f,					0.f,
					0.f,								 0.f,										-2 / (far - near),			0.f,
		-(right + left) / (right - left),	-(top + bottom) / (top - bottom),				 -(far + near) / (far - near),		1.f };
	}

	Core::Maths::mat4 Camera::CreateProjectionMatrix(float fov, const float aspectRatio, const float near, const float far)
	{
		fov *= (float)(M_PI / 180);
		float top = tanf(fov * 0.5f) * near;
		float bot = -top;
		float right = top * aspectRatio;
		float left = -right;

		return { (2.f * near) / (right - left),			0.f,						(right + left) / (right - left),			   0.f,
						  0.f,				  (2.f * near) / (top - bot),				(top + bot) / (top - bot),						 0.f,
						  0.f,							0.f,						 -(far + near) / (far - near),					 (-2.f * far * near) / (far - near),
						  0.f,							0.f,						-1.f,											 0.f
		};
	}

	Core::Maths::mat4 Camera::GetViewMatrix()
	{
		return Resources::Transform::LookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
	}

	void Camera::MoveCamera(MovCamera direction, float deltaTime)
	{
		if (!m_isLookingAt)
		{
			vec3 front = vec3(m_cameraFront.m_x, 0, m_cameraFront.m_z).Normalize();
			vec3 right = vec3(m_cameraRight.m_x, 0, m_cameraRight.m_z).Normalize();

			float velocity = m_movementSpeed * deltaTime;
			if (direction == MovCamera::FORWARD)
				m_cameraPos += front * velocity;
			if (direction == MovCamera::BACKWARD)
				m_cameraPos -= front * velocity;
			if (direction == MovCamera::LEFT)
				m_cameraPos += right * velocity;
			if (direction == MovCamera::RIGHT)
				m_cameraPos -= right * velocity;
		}
		else
		{
			float velocity = m_movementSpeed * deltaTime;
			if (direction == MovCamera::FORWARD && m_camAngleY < 1.0f)
			{
				m_camAngleY += velocity;
			}
			if (direction == MovCamera::BACKWARD && m_camAngleY > 0.0f)
			{
				m_camAngleY -= velocity;
			}
			if (direction == MovCamera::LEFT)
			{
				m_camAngleX -= velocity;
				m_camAngleZ -= velocity;
			}
			if (direction == MovCamera::RIGHT)
			{
				m_camAngleX += velocity;
				m_camAngleZ += velocity;
			}
		}

		UpdateVectors();
	}

	void Camera::MouseMoveCamera(float xOffset, float yOffset, bool contrainHeight)
	{
		if (m_isLookingAt)
		{
			return;
		}

		xOffset *= m_sensitivity;
		yOffset *= m_sensitivity;

		m_yaw += xOffset;
		m_pitch += yOffset;

		if (contrainHeight)
		{
			if (m_pitch > 89.0f)
			{
				m_pitch = 89.0f;
			}
			if (m_pitch < -89.0f)
			{
				m_pitch = -89.0f;
			}
		}

		UpdateVectors();
	}

	void Camera::SetIsLookingAt(bool isLookingAt)
	{
		m_isLookingAt = isLookingAt;
		UpdateVectors();
	}

	void Camera::SetTarget(vec3 target)
	{
		m_targetPos = target;
		UpdateVectors();
	}

	void Camera::UpdateVectors()
	{
		if (!m_isLookingAt)
		{
			// Calculate the new Front vector
			float yaw, pitch;
			yaw = m_yaw * (float)(M_PI / 180);
			pitch = m_pitch * (float)(M_PI / 180);

			vec3 front{ 0.f, 0.f,0.f };
			front.m_x = cosf(yaw) * cosf(pitch);
			front.m_y = sinf(pitch);
			front.m_z = sinf(yaw) * cosf(pitch);

			//re - calculate the right and up
			m_cameraFront = front.Normalize();
			m_cameraRight = m_worldUp.Cross(front).Normalize();
			m_cameraUp = front.Cross(m_cameraRight).Normalize();
		}
		else
		{
			float camX = sinf(m_camAngleX) * m_radius;
			float camY = sinf(m_camAngleY) * m_radius;
			float camZ = cosf(m_camAngleZ) * m_radius;

			m_cameraPos = vec3(camX, camY, camZ) + m_targetPos;
			m_cameraFront = (m_targetPos - m_cameraPos).Normalize();
			m_cameraPos = m_cameraPos - (m_cameraFront * 0.5f);
			m_cameraRight = m_worldUp.Cross(m_cameraFront).Normalize();
			m_cameraUp = m_cameraFront.Cross(m_cameraRight).Normalize();
		}
	}
}