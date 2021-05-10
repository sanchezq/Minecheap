#pragma once
class LifeComponent
{
public:
	LifeComponent() = delete;
	LifeComponent(const float hp);
	LifeComponent(const LifeComponent& other) = delete;
	LifeComponent& operator=(const LifeComponent& other) = default;
	~LifeComponent() = default;
	
	void SetComponent(const float life);

	void SetActualHP(const float hp);
	void SetMaxHP(const float maxHP);

	float GetActualHP() const ;
	float GetMaxHP() const;

	void TakeDamage(const float damage);
	void Heal();

	bool isDead() const;

private:
	float m_hp;
	float m_maxHp;
};

