#pragma once

#include "GameObject.h"
#include "LifeComponent.h"


class Entity : public GameObject
{
public:
	Entity();
	Entity(const Entity& other) = delete;
	Entity& operator=(const Entity& other) = default;
	~Entity() = default;

	virtual void Update(const float deltaTime) override = 0;
	
	const float GetHealth() const;
	void SetHealth(const float healthPoint);

	LifeComponent& MutateLifeComponent();

protected:
	LifeComponent m_lifeCpnt;
	float m_damage = 0.0f;
	float m_reach = 0.0f;
};

