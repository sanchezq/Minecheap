#pragma once
#include "Maths/vec4.h"
#include "Maths/vec3.h"
#include "Entity.h"

class Raycast
{
public:
	Raycast() = delete;
	Raycast(const Raycast& other) = delete;
	Raycast& operator=(const Raycast& other) = delete;
	~Raycast() = delete;

	static Core::Maths::vec4 RayTestCollide(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax);
	static Core::Maths::vec4 RayTestBreakBlock(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax);
	static Core::Maths::vec4 RayTestPlaceBlock(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax);
	static Entity* RayTestHitEnemies(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax);


private:

	static bool rayBoxIntersect(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, Core::Maths::vec3& minCorner, Core::Maths::vec3& maxCorner, const float distanceMax);
	static bool TestNeg(const float a, const float maxA, const bool negA);

	static const float ms_precision;
};

