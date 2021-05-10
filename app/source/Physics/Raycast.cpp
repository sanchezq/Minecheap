#include "App.h"
#include "GameManager.h"
#include "Raycast.h"

const float Raycast::ms_precision = 20.f;

Core::Maths::vec4 Raycast::RayTestCollide(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax)
{
	// Avoid collision bug if coord negative
	if (startPoint.m_x < 0.0f || startPoint.m_z < 0.0f)
	{
		return { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	dir.Normalize();

	const float	minX = startPoint.m_x,
		minY = startPoint.m_y,
		minZ = startPoint.m_z,
		maxX = minX + (dir.m_x * distanceMax),
		maxY = minY + (dir.m_y * distanceMax),
		maxZ = minZ + (dir.m_z * distanceMax),
		addX = (maxX - minX) / ms_precision,
		addY = (maxY - minY) / ms_precision,
		addZ = (maxZ - minZ) / ms_precision;

	float	x = minX,
		y = minY,
		z = minZ;

	const bool	negX = x > maxX,
		negY = y > maxY,
		negZ = z > maxZ;

	while (TestNeg(x, maxX, negX) && TestNeg(y, maxY, negY) && TestNeg(z, maxZ, negZ))
	{
		BlockID block = App::GetGameManager().GetWorld().GetBlockType((int)x, (int)y, (int)z);
		if (block != BlockID::AIR)
		{
			return { x, y, z, (float)block };
		}

		x += addX;
		y += addY;
		z += addZ;
	}

	return { 0.0f, 0.0f, 0.0f, 0.0f };

}

Core::Maths::vec4 Raycast::RayTestBreakBlock(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax)
{
	// Avoid collision bug if coord negative
	if (startPoint.m_x < 0.0f || startPoint.m_z < 0.0f)
	{
		return { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	dir.Normalize();

	const float	minX = startPoint.m_x,
		minY = startPoint.m_y,
		minZ = startPoint.m_z,
		maxX = minX + (dir.m_x * distanceMax),
		maxY = minY + (dir.m_y * distanceMax),
		maxZ = minZ + (dir.m_z * distanceMax),
		addX = (maxX - minX) / ms_precision,
		addY = (maxY - minY) / ms_precision,
		addZ = (maxZ - minZ) / ms_precision;

	float	x = minX,
		y = minY,
		z = minZ;

	const bool	negX = x > maxX,
		negY = y > maxY,
		negZ = z > maxZ;

	while (TestNeg(x, maxX, negX) && TestNeg(y, maxY, negY) && TestNeg(z, maxZ, negZ))
	{
		BlockID block = App::GetGameManager().GetWorld().GetBlockType((int)x, (int)y, (int)z);
		if (block != BlockID::AIR && block != BlockID::WATER)
		{
			return { x, y, z, (float)block };
		}

		x += addX;
		y += addY;
		z += addZ;
	}

	return { 0.0f, 0.0f, 0.0f, 0.0f };

}

Core::Maths::vec4 Raycast::RayTestPlaceBlock(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax)
{
	// Avoid collision bug if coord negative
	if (startPoint.m_x < 0.0f || startPoint.m_z < 0.0f)
	{
		return { 0.0f, 0.0f, 0.0f, 0.0f };
	}

	dir.Normalize();

	const float	minX = startPoint.m_x,
		minY = startPoint.m_y,
		minZ = startPoint.m_z,
		maxX = minX + (dir.m_x * distanceMax),
		maxY = minY + (dir.m_y * distanceMax),
		maxZ = minZ + (dir.m_z * distanceMax),
		addX = (maxX - minX) / ms_precision,
		addY = (maxY - minY) / ms_precision,
		addZ = (maxZ - minZ) / ms_precision;

	float	x = minX,
		y = minY,
		z = minZ;

	const bool	negX = x > maxX,
		negY = y > maxY,
		negZ = z > maxZ;

	float lastX = 0, lastY = 0, lastZ = 0;

	while (TestNeg(x, maxX, negX) && TestNeg(y, maxY, negY) && TestNeg(z, maxZ, negZ))
	{
		BlockID block = App::GetGameManager().GetWorld().GetBlockType((int)x, (int)y, (int)z);
		if (block == BlockID::AIR || block == BlockID::WATER)
		{
			lastX = x;
			lastY = y;
			lastZ = z;
		}
		else
		{
			return { lastX, lastY, lastZ, (float)block };
		}

		x += addX;
		y += addY;
		z += addZ;
	}

	return { 0.0f, 0.0f, 0.0f, 0.0f };
}

Entity* Raycast::RayTestHitEnemies(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, const float distanceMax)
{
	if (startPoint.m_x < 0.0f || startPoint.m_z < 0.0f)
	{
		return nullptr;
	}

	dir.Normalize();


	Zombie* enemy = App::GetGameManager().GetWorld().m_zombie;
	Core::Maths::vec3 minCorner{ 0, 0, 0 }, maxCorner{ 0, 0, 0 };

	if (enemy != nullptr)
	{
		minCorner.m_x = std::fminf((App::GetGameManager().GetWorld().m_zombie->GetPosition().m_x - App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_x / 2),
			(App::GetGameManager().GetWorld().m_zombie->GetPosition().m_x + App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_x / 2));

		minCorner.m_y = App::GetGameManager().GetWorld().m_zombie->GetPosition().m_y; //- App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_y / 2;

		minCorner.m_z = std::fminf((App::GetGameManager().GetWorld().m_zombie->GetPosition().m_z - App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_z / 2),
			(App::GetGameManager().GetWorld().m_zombie->GetPosition().m_z + App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_z / 2));


		maxCorner.m_x = std::fmaxf((App::GetGameManager().GetWorld().m_zombie->GetPosition().m_x - App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_x / 2),
			(App::GetGameManager().GetWorld().m_zombie->GetPosition().m_x + App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_x / 2));

		maxCorner.m_y = App::GetGameManager().GetWorld().m_zombie->GetPosition().m_y + App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_y;

		maxCorner.m_z = std::fmaxf((App::GetGameManager().GetWorld().m_zombie->GetPosition().m_z - App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_z / 2),
			(App::GetGameManager().GetWorld().m_zombie->GetPosition().m_z + App::GetGameManager().GetWorld().m_zombie->GetScaleBox().m_z / 2));


		if (rayBoxIntersect(startPoint, dir, minCorner, maxCorner, distanceMax))
		{
			return enemy;
		}

	}

	return nullptr;
}

bool Raycast::rayBoxIntersect(const Core::Maths::vec3& startPoint, Core::Maths::vec3 dir, Core::Maths::vec3& minCorner, Core::Maths::vec3& maxCorner, const float distanceMax)
{
	Core::Maths::vec3 dirfrac{ 0, 0, 0 };

	// r.dir is unit direction vector of ray
	dirfrac.m_x = 1.0f / dir.m_x;
	dirfrac.m_y = 1.0f / dir.m_y;
	dirfrac.m_z = 1.0f / dir.m_z;
	// lb is the corner of AABB with minimal coordinates - left bottom, rt is maximal corner
	// r.org is origin of ray
	float t1 = (minCorner.m_x - startPoint.m_x) * dirfrac.m_x;
	float t2 = (maxCorner.m_x - startPoint.m_x) * dirfrac.m_x;
	float t3 = (minCorner.m_y - startPoint.m_y) * dirfrac.m_y;
	float t4 = (maxCorner.m_y - startPoint.m_y) * dirfrac.m_y;
	float t5 = (minCorner.m_z - startPoint.m_z) * dirfrac.m_z;
	float t6 = (maxCorner.m_z - startPoint.m_z) * dirfrac.m_z;

	float tmin = std::fmaxf(std::fmaxf(std::fminf(t1, t2), std::fminf(t3, t4)), std::fminf(t5, t6));
	float tmax = std::fminf(std::fminf(std::fmaxf(t1, t2), std::fmaxf(t3, t4)), std::fmaxf(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		return false;
	}

	//t = tmin;

	if (tmin < distanceMax)
	{
		return true;
	}

	return false;
}

bool Raycast::TestNeg(const float a, const float maxA, const bool negA)
{
	return ((!negA && a <= maxA) || (negA && a >= maxA));
}

