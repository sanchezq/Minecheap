#include "Zombie.h"

#include "App.h"
#include "GameManager.h"
#include "Raycast.h"

Zombie::Zombie(const std::vector<float>& meshData, const Core::Maths::vec3& pos, const Core::Maths::vec3& scaleCollideBox, const float damage, const float reach, const float life, const bool gravity)
{
	//TODO Use a real rotation
	m_rotation.Set(0, 0, 0);
	m_isGravity = gravity;
	m_scaleCollisionBox = scaleCollideBox;
	m_damage = damage;
	m_reach = reach;
	m_lifeCpnt.SetComponent(life);
	m_attackTimer = m_timeReloadAttack;

	m_position = pos;

	m_model = LowRenderer::Model(meshData);
	//unsigned int texture = Resources::ResourcesManager::GetTexture(filePath);
	//model->SetTextureID(texture);
	m_objectGraphic = new Core::DataStructure::Graph(&m_model, 1.f, {0.f, 0.f, 0.f}, Core::Maths::vec4(1, 1, 1, 1));

	m_objectGraphic->SetTransform(Resources::Transform::CreateTranslateMatrix({ m_position.m_x, m_position.m_y + (m_scaleCollisionBox.m_y / 2), m_position.m_z }));
	m_objectGraphic->SetModelScale(m_scaleCollisionBox);

	App::GetGameManager().MutateScene().GetRoot()->AddChild(m_objectGraphic);
}

Zombie::~Zombie()
{
	if (m_sound != nullptr)
	{
		m_sound->drop();
	}
	if (m_objectGraphic != nullptr)
	{
		delete m_objectGraphic;
	}
}

bool Zombie::TargetPlayer(const float deltaTime)
{
	if (m_playerDistance < 15 && m_playerDistance > 1.5f)
	{
		Core::Maths::vec3 dir = (App::GetGameManager().GetWorld().m_player.GetPosition() - m_position);

		dir.m_y = 0;
		dir = dir.Normalize();

		BlockID testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, dir, 0.6f).m_w,
		testBlockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, dir, 0.6f).m_w;


		if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
		{
			m_position += dir * 2.0f * deltaTime;
		}
		else if (testBlockBottom != BlockID::AIR && testBlockTop == BlockID::AIR && !m_isJump)
		{
			m_fallSpeed = 4;
			m_isJump = true;
		}

		return true;
	}

	return false;
}

void Zombie::Update(const float deltaTime)
{
	m_playerDistance = (App::GetGameManager().GetWorld().m_player.GetPosition() - m_position).GetMagnitude();

	if (m_playerDistance > 50)
	{
		return;
	}

	//"kill" zombie
	if (m_lifeCpnt.isDead())
	{
		m_position = Core::Maths::vec3{ 1000, 10, 1000 };
		m_objectGraphic->SetTransform(Resources::Transform::CreateTranslateMatrix({ m_position.m_x, m_position.m_y + (m_scaleCollisionBox.m_y / 2), m_position.m_z }));
		return;
	}

	//avoid glitch with gravity
	if (deltaTime >= 1.5f)
	{
		return;
	}

	//Update Zombie State
	if (!TargetPlayer(deltaTime))
	{
		m_waitingTime -= deltaTime;
		if (m_waitingTime <= 0)
		{
			m_waitingTime = (float)3 + (float)(rand() % 5);
			if (m_actualMovement == EnemyMove::NONE)
			{
				m_actualMovement = (EnemyMove)(1 + (rand() % 5));
			}
			else
			{
				m_actualMovement = EnemyMove::NONE;
			}
		}
		Move(deltaTime);
	}

	//Check AttackPlayer
	if (m_playerDistance <= 1.5f)
	{
		m_attackTimer -= deltaTime;
		if (m_attackTimer <= 0)
		{
			App::GetGameManager().MutateWorld().m_player.MutateLifeComponent().TakeDamage(m_damage);
			App::GetGameManager().MutateWorld().m_player.m_hit = App::GetGameManager().MutateSound().Play2D("resources/Sounds/hitsound.ogg", false);
			App::GetGameManager().MutateSound().Volume(App::GetGameManager().MutateWorld().m_player.m_hit, App::GetGameManager().MutateWorld().m_player.m_hitVolume);
			m_attackTimer = m_timeReloadAttack;
		}
	}

	UpdateGravity(deltaTime);
	m_objectGraphic->SetTransform(Resources::Transform::CreateTranslateMatrix({ m_position.m_x, m_position.m_y + (m_scaleCollisionBox.m_y / 2), m_position.m_z }));

	App::GetGameManager().MutateSound().SetPosition(m_sound, m_position);
}

void Zombie::Move(const float deltaTime)
{
	BlockID testBlockBottom, testBlockTop;

	switch (m_actualMovement)
	{
	case EnemyMove::NONE:
		break;

	case EnemyMove::RIGHT:

		testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { 1, 0, 0 }, 0.6f).m_w;
		testBlockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, { 1, 0, 0 }, 0.6f).m_w;

		if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
		{
			m_position.m_x += 1.0f * deltaTime;
		}
		else if (testBlockBottom != BlockID::AIR && testBlockTop == BlockID::AIR && !m_isJump)
		{
			m_fallSpeed = 6;
			m_isJump = true;
		}
		else
		{
			m_waitingTime = 0;
		}
		break;

	case EnemyMove::LEFT:

		testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { -1, 0, 0 }, 0.6f).m_w;
		testBlockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, { -1, 0, 0 }, 0.6f).m_w;

		if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
		{
			m_position.m_x -= 1.0f * deltaTime;
		}
		else if (testBlockBottom != BlockID::AIR && testBlockTop == BlockID::AIR && !m_isJump)
		{
			m_fallSpeed = 6;
			m_isJump = true;
		}
		else
		{
			m_waitingTime = 0;
		}
		break;

	case EnemyMove::FORWARD:

		testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { 0, 0, 1 }, 0.6f).m_w;
		testBlockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, { 0, 0, 1 }, 0.6f).m_w;

		if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
		{
			m_position.m_z += 1.0f * deltaTime;
		}
		else if (testBlockBottom != BlockID::AIR && testBlockTop == BlockID::AIR && !m_isJump)
		{
			m_fallSpeed = 6;
			m_isJump = true;
		}
		else
		{
			m_waitingTime = 0;
		}
		break;

	case EnemyMove::BACKWARD:

		testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { 0, 0, -1 }, 0.6f).m_w;
		testBlockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, { 0, 0, -1 }, 0.6f).m_w;

		if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
		{
			m_position.m_z -= 1.0f * deltaTime;
		}
		else if (testBlockBottom != BlockID::AIR && testBlockTop == BlockID::AIR && !m_isJump)
		{
			m_fallSpeed = 6;
			m_isJump = true;
		}
		else
		{
			m_waitingTime = 0;
		}
		break;

	default:
		break;
	}
}
