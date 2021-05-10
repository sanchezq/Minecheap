#include "Entity.h"

Entity::Entity() : 
	m_lifeCpnt(100)
{
}

const float Entity::GetHealth() const
{
	return m_lifeCpnt.GetActualHP();
}

void Entity::SetHealth(const float healthPoint)
{
	m_lifeCpnt.SetActualHP(healthPoint);
}

LifeComponent& Entity::MutateLifeComponent()
{
	return m_lifeCpnt;
}
