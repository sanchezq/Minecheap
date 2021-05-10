#include "GameObject.h"
#include "Raycast.h"
#include "App.h"
#include "Maths/vec3.h"
#include "BlockID.h"

void GameObject::UpdateGravity(const float deltaTime)
{
	if (!m_isGravity)
	{
		return;
	}

	if ((BlockID)(int)Raycast::RayTestCollide(m_position, { 0, -1, 0 }, 0.2f ).m_w != BlockID::AIR)
	{
		m_fallSpeed = 0;
	}
	//increase fall speed if the limit is not reached
	else if (m_fallSpeed > -(9.81f * 1.75f))
	{
		m_fallSpeed -= 9.81f * deltaTime;
	}
	

	//PATCH , need rework
	if (deltaTime > 1.0f)
	{
		m_fallSpeed = 0;
	}

	m_position.m_y += m_fallSpeed * deltaTime;

}


const Core::Maths::vec3& GameObject::GetPosition() const
{
	return m_position;
}

const Core::Maths::vec3& GameObject::GetRotation() const
{
	return m_rotation;
}

const Core::Maths::vec3& GameObject::GetScaleBox() const
{
	return m_scaleCollisionBox;
}

Core::Maths::vec3& GameObject::MutatePosition()
{
	return m_position;
}

Core::Maths::vec3& GameObject::MutateRotation()
{
	return m_rotation;
}

Core::Maths::vec3& GameObject::MutateScaleBox()
{
	return m_scaleCollisionBox;
}

void GameObject::SetPosition(const Core::Maths::vec3& vec)
{
	m_position = vec;
}
