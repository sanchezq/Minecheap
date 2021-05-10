#pragma once

#include "Entity.h"
#include "Player.h"

enum class EnemyMove
{
	NONE = 0,
	RIGHT,
	LEFT,
	FORWARD,
	BACKWARD
};

class Enemy : public Entity
{
public:
	Enemy() = default;
	Enemy(const Enemy& other) = delete;
	Enemy& operator=(const Enemy& other) = delete;
	~Enemy() = default;

	void UpdateGravity(const float deltaTime) override;
	virtual bool TargetPlayer(const float deltaTime) = 0;
	virtual void Update(const float deltaTime) override = 0;


protected:

	bool m_isJump = false;
};

