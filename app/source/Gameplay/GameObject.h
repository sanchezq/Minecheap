#pragma once

#include "DataStructure/Graph.h"

class GameObject
{
public:

	GameObject() = default;
	GameObject(const GameObject& other) = delete;
	GameObject& operator=(const GameObject& other) = default;
	~GameObject() = default;

	virtual void UpdateGravity(const float deltaTime);

	virtual void Update(const float deltaTime) = 0;

	const Core::Maths::vec3& GetPosition() const;
	const Core::Maths::vec3& GetRotation() const;
	const Core::Maths::vec3& GetScaleBox() const;
	Core::Maths::vec3& MutatePosition();
	Core::Maths::vec3& MutateRotation();
	Core::Maths::vec3& MutateScaleBox();

	void SetPosition(const Core::Maths::vec3& vec);

protected:

	Core::DataStructure::Graph* m_objectGraphic = nullptr;

	Core::Maths::vec3 m_position = {0, 0, 0};
	Core::Maths::vec3 m_rotation = { 0, 0, 0 };
	Core::Maths::vec3 m_scaleCollisionBox = { 1, 1, 1 };
	bool m_isGravity = false;

	float m_fallSpeed = 0.0f;

	// CollisionShape
};

