#include "Enemy.h"
#include "Raycast.h"

void Enemy::UpdateGravity(const float deltaTime)
{
	if (!m_isGravity)
	{
		return;
	}


	BlockID blockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, { 0, 1, 0 }, 0.2f).m_w;
	BlockID blockBot = (BlockID)(int)Raycast::RayTestCollide(m_position, { 0, -1, 0 }, 0.1f).m_w;

	if (blockTop != BlockID::AIR && blockBot != BlockID::WATER)
	{
		m_fallSpeed = -1;
		m_isJump = false;
	}



	if (blockBot != BlockID::AIR && !m_isJump)
	{
		m_fallSpeed = 0;

		//calculate the int position of the block
		int EntierY = (int)(m_position.m_y + 0.5f);
		if (m_position.m_y < (float)EntierY)
		{
			m_position.m_y = (float)EntierY;
		}
	}
	//increase fall speed if the limit is not reached
	else if (m_fallSpeed > -20.0f)
	{
		m_fallSpeed -= 9.81f * 2 * deltaTime;
		m_isJump = false;
	}


	//PATCH , a rework
	if (deltaTime > 2.0f)
	{
		m_fallSpeed = 0;
	}

	m_position.m_y += m_fallSpeed * deltaTime;

}
