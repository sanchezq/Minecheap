#pragma once
#include "SoundManager.h"
#include "Enemy.h"
#include "Player.h"

class Zombie : public Enemy
{
public:
	Zombie() = delete;
	Zombie(const std::vector<float>& meshData, const Core::Maths::vec3& pos = { 0, 0, 0 }, const Core::Maths::vec3& scaleCollideBox = { 1, 2, 1 }, const float damage = 10, const float reach = 4, const float life = 50, const bool gravity = true);
	Zombie(const Zombie& other) = delete;
	Zombie& operator=(const Zombie& other) = delete;
	~Zombie();

	bool TargetPlayer(const float deltaTime) override;
	void Update(const float deltaTime) override;
	void Move(const float deltaTime);

	irrklang::ISound* m_sound = nullptr;
	irrklang::ISound* m_hit = nullptr;
	float m_volumeHit = 0.1f;
private:
	LowRenderer::Model m_model;
	EnemyMove m_actualMovement = EnemyMove::NONE;
	float m_waitingTime = 5;

	float m_playerDistance = 0;
	float m_timeReloadAttack = 2.5f;
	float m_attackTimer = 0;
};