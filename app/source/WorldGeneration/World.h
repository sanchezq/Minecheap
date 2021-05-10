#pragma once

#include "Chunk.h"

#include "Player.h"
#include "Zombie.h"

#define SUPER_CHUNK_X 3
#define SUPER_CHUNK_Z 3

#define CAVERN_LEVEL 10
#define STONE_LEVEL 45
#define WATER_LEVEL 70
#define PLAIN_LEVEL 80



#define CHUNK_GENERATE 3

class World
{

public:
    Resources::Scene* m_scene;
    Chunk* m_chunks[SUPER_CHUNK_X][SUPER_CHUNK_Z] = { nullptr };
    int m_nbChunks = 0;

    Player m_player;
    Zombie* m_zombie = nullptr;

    

    World() = default;
    World(const World& other) = delete;
    World& operator=(const World& other) = delete;
    ~World();

    void Initialize(Resources::Scene* scene);

    void LoadSave();
    void InitNewGame();

    void ForceUpdate();
    void World::Clear();

    void Generate();
    void Populate();

    void CreateTree(const int x, const int y, const int z);
    void BuildLeaves(const int x, const int y, const int z);

    BlockID GetBlockType(const int x, const int y, const int z) const;
    void Set(const int x, const int y, const int z, const BlockID type);

    void Render();


    void UpdateBlockArround(const int x, const int y, const int z, const float timer);
    void UpdateBlock(const int x, const int y, const int z);

private:
    float Perlin3D(const float x, const float y, const float z);
    Core::Maths::vec3 m_seed{ 0,0,0 };

};