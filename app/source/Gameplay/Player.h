#pragma once

#include "Entity.h"
#include "Maths/vec3.h"
#include "InventoryComponent.h"
#include "SoundManager.h"

enum class PlayerMove
{
	RIGHT = 0,
	LEFT,
	FORWARD,
	BACKWARD,
	JUMP
};

class Player : public Entity
{
public:
	Player() = default;
	Player(const Player& other) = delete;
	Player& operator=(const Player& other) = default;
	~Player();

	bool Initialize(const Core::Maths::vec3& pos, const Core::Maths::vec3& scaleCollideBox = { 1, 2, 1 }, const int inventorySize = 36, const float damage = 1, const float reach = 4, const float life = 100, const bool gravity = true);

	void Move(const PlayerMove& move, const float deltaTime);
	void Update(const float deltaTime) override;
	void BreakBlock();
	void PlaceBlock();

	bool isInWater();

	const InventoryComponent& GetInventory() const;
	InventoryComponent& GetMutateInventory();
	void  FillOneInventorySlot(const int slotNb, const int id, const int quantity);

	void SetSelectedIndex(const unsigned int index);
	const unsigned int GetSelectedIndex() const;

	void AddBlockToUpdate(const int x, const int y, const int z, const float timer);
	irrklang::ISound* m_hit = nullptr;
	float m_hitVolume = 0.4f;

	irrklang::ISound* m_block = nullptr;
	float m_volumeBlock = 0.4f;
private:
	void UpdateGravity(const float deltaTime) override;
	void CalculateFallDamages();

	unsigned int m_selectedIndex = 0;
	InventoryComponent m_inventory;

	std::vector<Core::Maths::vec4> blocksToUpdate;

	bool m_isJump = false;

	float m_highestYduringJump = 0;
};

