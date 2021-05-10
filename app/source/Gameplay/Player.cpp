#include "Player.h"

#include "LifeComponent.h"
#include "Raycast.h"
#include "App.h"
#include "BlockID.h"

#include <iostream>
#include "GameManager.h"

Player::~Player()
{
	if (m_hit)
	{
		m_hit->drop();
	}
}

bool Player::Initialize(const Core::Maths::vec3& pos, const Core::Maths::vec3& scaleCollideBox, const int inventorySize, const float damage, const float reach, const float life, const bool gravity)
{
	m_inventory.SetSize(inventorySize);
	m_objectGraphic = nullptr;
	m_rotation.Set(0.0f, 0.0f, 0.0f);

	m_isGravity = gravity;
	m_scaleCollisionBox.Set(scaleCollideBox.m_x, scaleCollideBox.m_y, scaleCollideBox.m_z);
	m_damage = damage;
	m_reach = reach;
	m_lifeCpnt.SetComponent(life);

	m_position.Set(pos.m_x, pos.m_y, pos.m_z);
	App::GetGameManager().MutateScene().m_camera.m_cameraPos.Set(m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y - 0.5f, m_position.m_z);

	return true;
}

void Player::UpdateGravity(const float deltaTime)
{
	if (!m_isGravity)
	{
		return;
	}

	BlockID blockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, { 0, 1, 0 }, 0.4f).m_w;
	BlockID blockBot = (BlockID)(int)Raycast::RayTestCollide(m_position, { 0, -1, 0 }, 0.1f).m_w;

	//Check if there is a block which prevents the player from jumping
	if (blockTop!= BlockID::AIR && App::GetGameManager().MutateBlockDataBase().GetData(blockBot).m_classType != BlockClassType::LIQUID)
	{
		m_fallSpeed = -1;
		m_isJump = false;
	}

	//Calculate Highest Y when player is falling or jumping
	if (m_fallSpeed < 0 && m_position.m_y > m_highestYduringJump && App::GetGameManager().MutateBlockDataBase().GetData(blockBot).m_classType != BlockClassType::LIQUID)
	{
		m_highestYduringJump = m_position.m_y;
	}

	
	//Check if player is in Liquid
	if (App::GetGameManager().MutateBlockDataBase().GetData(blockBot).m_classType == BlockClassType::LIQUID)
	{
		m_highestYduringJump = 0;

		if (m_fallSpeed > -1.0f)
		{
			m_fallSpeed -= 9.81f * 0.5f * deltaTime;
		}
		else
		{
			m_fallSpeed = -1.0f;
		}
	}
	//Check if player touch the ground
	else if (blockBot != BlockID::AIR && !m_isJump)
	{
		CalculateFallDamages();
		m_fallSpeed = 0;

		//calculate the int position of the block
		int EntierY = (int)(m_position.m_y + 0.5f);
		if (m_position.m_y < (float)EntierY)
		{
			m_position.m_y = (float)EntierY;
		}
	}
	//increase fall speed if the limit is not reached
	else if (m_fallSpeed > -20.0f)
	{
		m_fallSpeed -= 9.81f * 2 * deltaTime;
		m_isJump = false;
	}

	m_position.m_y += m_fallSpeed * deltaTime;

}

void Player::Update(const float deltaTime)
{
	if (deltaTime >= 1.5f)
	{
		return;
	}

	UpdateGravity(deltaTime);

	if (m_position.m_y <= 0)
	{
		m_lifeCpnt.TakeDamage(5);
		m_position.m_y = 100;
		m_fallSpeed = 0;
	}

	int maxI = (int)blocksToUpdate.size();
	for (int i = 0; i < maxI; i++)
	{
		if (blocksToUpdate[i].m_w > 0.f)
		{
			blocksToUpdate[i].m_w -= deltaTime;
		}
		else
		{
			blocksToUpdate[i].m_w = App::GetGameManager().MutateBlockDataBase().GetData((BlockID)App::GetGameManager().GetWorld().GetBlockType((int)blocksToUpdate[i].m_x, (int)blocksToUpdate[i].m_y, (int)blocksToUpdate[i].m_z)).m_updateTime;
			App::GetGameManager().MutateWorld().UpdateBlock((int)blocksToUpdate[i].m_x, (int)blocksToUpdate[i].m_y, (int)blocksToUpdate[i].m_z);
			blocksToUpdate.erase(blocksToUpdate.begin() + i);
			maxI--;
		}
	}
	App::GetGameManager().MutateWorld().Render();
	App::GetGameManager().MutateScene().m_camera.m_cameraPos.Set(m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y - 0.5f, m_position.m_z);
}

void Player::Move(const PlayerMove& move, const float deltaTime)
{
	App::GetGameManager().MutateScene().m_camera.m_movementSpeed = 5;
	BlockID testBlockBottom, testBlockTop;
	bool isBlockBottomLiquid, isBlockTopLiquid;

	switch (move)
	{
		case PlayerMove::FORWARD :

			testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_x, 0, App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_z }, 0.4f).m_w;
			testBlockTop = (BlockID)(int)Raycast::RayTestCollide(App::GetGameManager().MutateScene().m_camera.m_cameraPos, { App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_x, 0, App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_z }, 0.4f).m_w;

			if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
			{
				App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::FORWARD, deltaTime);
			}
			else
			{
				isBlockBottomLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockBottom).m_classType == BlockClassType::LIQUID);
				isBlockTopLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockTop).m_classType == BlockClassType::LIQUID);

				if (isBlockBottomLiquid && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::FORWARD, deltaTime * 0.5f);
				}
				else if (isBlockBottomLiquid && testBlockTop == BlockID::AIR)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::FORWARD, deltaTime * 0.5f);
				}
				else if (testBlockBottom == BlockID::AIR && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::FORWARD, deltaTime * 0.5f);
				}
			}
			break;

		case PlayerMove::BACKWARD :

			testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { -App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_x, 0, -App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_z }, 0.4f).m_w;
			testBlockTop = (BlockID)(int)Raycast::RayTestCollide(App::GetGameManager().MutateScene().m_camera.m_cameraPos, { -App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_x, 0, -App::GetGameManager().MutateScene().m_camera.m_cameraFront.m_z }, 0.4f).m_w;

			if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
			{
				App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::BACKWARD, deltaTime);
			}
			else
			{
				isBlockBottomLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockBottom).m_classType == BlockClassType::LIQUID);
				isBlockTopLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockTop).m_classType == BlockClassType::LIQUID);

				if (isBlockBottomLiquid && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::BACKWARD, deltaTime * 0.5f);
				}
				else if (isBlockBottomLiquid && testBlockTop == BlockID::AIR)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::BACKWARD, deltaTime * 0.5f);
				}
				else if (testBlockBottom == BlockID::AIR && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::BACKWARD, deltaTime * 0.5f);
				}
			}
			break;

		case PlayerMove::RIGHT: 

			testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { -App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_x, 0, -App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_z }, 0.4f).m_w;
			testBlockTop = (BlockID)(int)Raycast::RayTestCollide(App::GetGameManager().MutateScene().m_camera.m_cameraPos, { -App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_x, 0, -App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_z }, 0.4f).m_w;

			if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
			{
				App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::RIGHT, deltaTime);
			}
			else
			{
				isBlockBottomLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockBottom).m_classType == BlockClassType::LIQUID);
				isBlockTopLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockTop).m_classType == BlockClassType::LIQUID);

				if (isBlockBottomLiquid && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::RIGHT, deltaTime * 0.5f);
				}
				else if (isBlockBottomLiquid && testBlockTop == BlockID::AIR)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::RIGHT, deltaTime * 0.5f);
				}
				else if (testBlockBottom == BlockID::AIR && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::RIGHT, deltaTime * 0.5f);
				}
			}
			break;
		
		case PlayerMove::LEFT:

			testBlockBottom = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + 0.5f, m_position.m_z }, { App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_x, 0, App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_z }, 0.4f).m_w;
			testBlockTop = (BlockID)(int)Raycast::RayTestCollide(App::GetGameManager().MutateScene().m_camera.m_cameraPos, { App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_x, 0, App::GetGameManager().MutateScene().m_camera.m_cameraRight.m_z }, 0.4f).m_w;

			if (testBlockBottom == BlockID::AIR && testBlockTop == BlockID::AIR)
			{
				App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::LEFT, deltaTime);
			}
			else
			{
				isBlockBottomLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockBottom).m_classType == BlockClassType::LIQUID);
				isBlockTopLiquid = (App::GetGameManager().MutateBlockDataBase().GetData(testBlockTop).m_classType == BlockClassType::LIQUID);

				if (isBlockBottomLiquid && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::LEFT, deltaTime * 0.5f);
				}
				else if (isBlockBottomLiquid && testBlockTop == BlockID::AIR)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::LEFT, deltaTime * 0.5f);
				}
				else if (testBlockBottom == BlockID::AIR && isBlockTopLiquid)
				{
					App::GetGameManager().MutateScene().m_camera.MoveCamera(LowRenderer::MovCamera::LEFT, deltaTime * 0.5f);
				}
			}
			break;

		case PlayerMove::JUMP: 

			testBlockBottom = (BlockID)(int)Raycast::RayTestCollide(m_position, { 0, -1, 0 }, 0.2f).m_w;
			testBlockTop = (BlockID)(int)Raycast::RayTestCollide({ m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y, m_position.m_z }, { 0, 1, 0 }, 0.4f).m_w;

			if (App::GetGameManager().MutateBlockDataBase().GetData(testBlockBottom).m_classType == BlockClassType::LIQUID &&
				(testBlockTop == BlockID::AIR || App::GetGameManager().MutateBlockDataBase().GetData(testBlockTop).m_classType == BlockClassType::LIQUID))
			{
				m_fallSpeed = 2.0f;
			}
			else if (testBlockBottom != BlockID::AIR && (testBlockTop == BlockID::AIR || App::GetGameManager().MutateBlockDataBase().GetData(testBlockTop).m_classType == BlockClassType::LIQUID))
			{
				CalculateFallDamages();

				m_fallSpeed = 6;
				m_isJump = true;
			}  
			break;

		default:
			break;
	}

	m_position = Core::Maths::vec3(App::GetGameManager().MutateScene().m_camera.m_cameraPos.m_x, App::GetGameManager().MutateScene().m_camera.m_cameraPos.m_y - m_scaleCollisionBox.m_y + 0.5f, App::GetGameManager().MutateScene().m_camera.m_cameraPos.m_z);
	
}


void Player::BreakBlock()
{
	Entity* entity = Raycast::RayTestHitEnemies(App::GetGameManager().MutateScene().m_camera.m_cameraPos, App::GetGameManager().MutateScene().m_camera.m_cameraFront, m_reach);
	if (entity)
	{
		if ((ItemID)m_inventory.GetItem(m_selectedIndex) >= ItemID::SWORD)
		{
			entity->MutateLifeComponent().TakeDamage(m_damage + App::GetGameManager().MutateItemDataBase().GetData((ItemID)m_inventory.GetItem(m_selectedIndex)).m_damage );
		}
		else
		{
			entity->MutateLifeComponent().TakeDamage(m_damage);
		}

		App::GetGameManager().MutateWorld().m_zombie->m_hit = App::GetGameManager().MutateSound().Play2D("resources/Sounds/hitzombie.ogg", false);
		App::GetGameManager().MutateSound().Volume(App::GetGameManager().MutateWorld().m_zombie->m_hit, App::GetGameManager().MutateWorld().m_zombie->m_volumeHit);
	}
	else
	{
		Core::Maths::vec4 bloc = Raycast::RayTestBreakBlock(App::GetGameManager().MutateScene().m_camera.m_cameraPos, App::GetGameManager().MutateScene().m_camera.m_cameraFront, m_reach);
		if ((BlockID)(int)bloc.m_w != BlockID::AIR)
		{
			m_inventory.AddOneItem((ItemID)App::GetGameManager().GetWorld().GetBlockType((int)bloc.m_x, (int)bloc.m_y, (int)bloc.m_z));
			App::GetGameManager().MutateWorld().Set((int)bloc.m_x, (int)bloc.m_y, (int)bloc.m_z, BlockID::AIR);
			App::GetGameManager().MutateWorld().Render();
			App::GetGameManager().MutateWorld().UpdateBlockArround((int)bloc.m_x, (int)bloc.m_y, (int)bloc.m_z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)App::GetGameManager().GetWorld().GetBlockType((int)bloc.m_x, (int)bloc.m_y, (int)bloc.m_z)).m_updateTime);

			m_block = App::GetGameManager().MutateSound().Play2D("resources/Sounds/block.ogg", false);
			App::GetGameManager().MutateSound().Volume(m_block, m_volumeBlock);
		}
	}
}

void Player::PlaceBlock()
{
	if ((ItemID)m_inventory.GetItem(m_selectedIndex) >= ItemID::STICK)
	{
		return;
	}

	Core::Maths::vec4 bloc = Raycast::RayTestPlaceBlock(App::GetGameManager().MutateScene().m_camera.m_cameraPos, App::GetGameManager().MutateScene().m_camera.m_cameraFront, m_reach);
	if ((BlockID)(int)bloc.m_w != BlockID::AIR && m_inventory.GetItemQuantity(m_selectedIndex) > 0)
	{
		if ((float)(Core::Maths::vec3(m_position.m_x, m_position.m_y + m_scaleCollisionBox.m_y/2, m_position.m_z)- Core::Maths::vec3(bloc.m_x, bloc.m_y, bloc.m_z)).GetMagnitude() < 1)
		{
			return;
		}

		App::GetGameManager().MutateWorld().Set((int)bloc.m_x, (int)bloc.m_y, (int)bloc.m_z, (BlockID)m_inventory.GetItem(m_selectedIndex));
		m_inventory.RemoveItem(m_selectedIndex);
		App::GetGameManager().MutateWorld().Render();
		AddBlockToUpdate((int)bloc.m_x, (int)bloc.m_y, (int)bloc.m_z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)App::GetGameManager().GetWorld().GetBlockType((int)bloc.m_x, (int)bloc.m_y, (int)bloc.m_z)).m_updateTime);

		m_block = App::GetGameManager().MutateSound().Play2D("resources/Sounds/block.ogg", false);
		App::GetGameManager().MutateSound().Volume(m_block, m_volumeBlock);
	}
}

bool Player::isInWater()
{
	if ((BlockID)(int)Raycast::RayTestCollide(App::GetGameManager().MutateScene().m_camera.m_cameraPos, { 0, 1, 0 }, 0.1f).m_w == BlockID::WATER)
	{
		return true;
	}

	return false;
}

void Player::CalculateFallDamages()
{
	if (m_fallSpeed < -1.0f)
	{
		float distance = m_highestYduringJump - m_position.m_y;

		if (distance > 3)
		{
			m_lifeCpnt.TakeDamage((distance - 3) * 5);
			
			m_hit = App::GetGameManager().MutateSound().Play2D("resources/Sounds/hitsound.ogg", false);
			App::GetGameManager().MutateSound().Volume(m_hit, m_hitVolume);
		}
	}

	m_highestYduringJump = 0;
}

const InventoryComponent& Player::GetInventory() const
{
	return m_inventory;
}

InventoryComponent& Player::GetMutateInventory()
{
	return m_inventory;
}

void Player::FillOneInventorySlot(const int slotNb, const int id, const int quantity)
{
	m_inventory.SetSlot(slotNb, id, quantity);
}

void Player::SetSelectedIndex(const unsigned int index)
{
	m_selectedIndex = index;
}

const unsigned int Player::GetSelectedIndex() const
{
	return m_selectedIndex;
}

void Player::AddBlockToUpdate(const int x, const int y, const int z, const float timer)
{
	blocksToUpdate.push_back({ (float)x, (float)y, (float)z, timer });
}

