#include "LifeComponent.h"

LifeComponent::LifeComponent(const float hp) :
	m_hp(hp), m_maxHp(hp)
{
}

void LifeComponent::SetComponent(const float life)
{
	SetActualHP(life);
	SetMaxHP(life);
}

void LifeComponent::SetActualHP(const float hp)
{
	m_hp = hp;
}

void LifeComponent::SetMaxHP(const float maxHP)
{
	m_maxHp = maxHP;	
}

float LifeComponent::GetActualHP() const
{
	return m_hp;
}

float LifeComponent::GetMaxHP() const
{
	return m_maxHp;
}

void LifeComponent::TakeDamage(const float damage)
{
	m_hp -= damage;
}

void LifeComponent::Heal()
{
	if (m_hp < m_maxHp)
	{
		m_hp = m_maxHp;
	}
}

bool LifeComponent::isDead() const
{
	return m_hp <= 0;
}
