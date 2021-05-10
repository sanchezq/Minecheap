#include "World.h"

#include "App.h"
#include "GameManager.h"

#include <glm/gtc/noise.hpp>

#include "Raycast.h"

World::~World()
{
    if (m_scene == nullptr)
    {
        return;
    }

    for (int x = 0; x < SUPER_CHUNK_X; x++)
    {
        for (int z = 0; z < SUPER_CHUNK_Z; z++)
        {
            delete m_chunks[x][z];
        }
    }

    delete m_zombie;
}

void World::Initialize(Resources::Scene* scene)
{
    if (scene == nullptr)
    {
        return;
    }
    m_scene = scene;

    for (int x = 0; x < SUPER_CHUNK_X; x++)
    {
        for (int z = 0; z < SUPER_CHUNK_Z; z++)
        {
            m_chunks[x][z] = new Chunk();
            m_scene->GetRoot()->AddChild(&m_chunks[x][z]->m_body);
        }
    }
}

void World::LoadSave()
{
    m_player.Initialize({ 0.f, 0.f, 0.f });

    //TODO init zombie here, not inside LoadGame() currently crashing if we dont do it in LoadGame

    //Resources::Mesh cube = Resources::Mesh::CreateCube();
    //m_zombie = new Zombie(cube.GetData(), { 0.0f, 200.0f, 0.0f});
    App::GetGameManager().LoadGame();
    ForceUpdate();
}

void World::InitNewGame()
{
    m_seed = Core::Maths::vec3{ (float)(rand() % 100000), (float)(rand() % 100000), (float)(rand() % 100000) };

    Generate();
    ForceUpdate();

    const int middle = (int)CHUNK_GENERATE * SIZE_CHUNK_X / 2;
    int topOfTheChunk = WATER_LEVEL;

    for (topOfTheChunk; GetBlockType(middle, topOfTheChunk, middle) > BlockID::AIR; topOfTheChunk++)
    {
        //Find the top of the chunk;
    }

    m_player.Initialize({ (float)middle, topOfTheChunk + 2.f, (float)middle });
    Resources::Mesh cube = Resources::Mesh::CreateCube();
    
    m_zombie = new Zombie(cube.GetData(), { (float)middle + 0.5f, topOfTheChunk + 20.f, (float)middle + 0.5f });
}

void World::ForceUpdate()
{
    for (int x = 0; x < SUPER_CHUNK_X; x++)
    {
        for (int z = 0; z < SUPER_CHUNK_Z; z++)
        {
            if (m_chunks[x][z] != NULL)
            {
                m_chunks[x][z]->Init();
            }
        }
    }
}

void World::Clear()
{
    for (int x = 0; x < SIZE_CHUNK_X * SUPER_CHUNK_X; x++)
    {
        for (int y = 0; y < SIZE_CHUNK_Y; y++)
        {
            for (int z = 0; z < SIZE_CHUNK_Z * SUPER_CHUNK_Z; z++)
            {
                Set(x, y, z, BlockID::AIR);
            }
        }
    }
}

float World::Perlin3D(const float x, const float y, const float z) 
{
    // TODO understand this algo
    //dunno how this works. copied it from somewhere.
    float ab = glm::perlin(glm::vec2(x, y));
    float bc = glm::perlin(glm::vec2(y, z));
    float ac = glm::perlin(glm::vec2(x, z));

    float ba = glm::perlin(glm::vec2(y, x));
    float cb = glm::perlin(glm::vec2(z, y));
    float ca = glm::perlin(glm::vec2(z, x));

    float abc = ab + bc + ac + ba + cb + ca;
    return abc / 6.f;
}

// TODO Use less memory  or use Heap
void World::Generate()
{
    m_nbChunks = CHUNK_GENERATE * CHUNK_GENERATE;

    const float noiseScale = .07f,
                noiseUsed = .15f,
                SMOOTH = 50.f,
                BIG = 65.f;
    int yMax;

    for (int x = 0; x < CHUNK_GENERATE * SIZE_CHUNK_X; x++)
    {
        for (int z = 0; z < CHUNK_GENERATE * SIZE_CHUNK_Z; z++)
        {
            yMax = STONE_LEVEL + (int)((glm::simplex(glm::vec2{ (x + m_seed.m_x) / SMOOTH, (z + m_seed.m_z) / SMOOTH }) + 1.f) / 2.f * BIG);

            for (int y = 0; y < yMax; y++)
            {
                if (y == yMax - 1)
                {
                    Set(x, y, z, BlockID::GRASS);
                }
                else if (y >= yMax - 3)
                {
                    Set(x, y, z, BlockID::DIRT);
                }
                else
                {
                    Set(x, y, z, BlockID::STONE);
                }
            }

            if (yMax < WATER_LEVEL)
            {
                for (int y = yMax; y < WATER_LEVEL; y++)
                {
                    Set(x, y, z, BlockID::WATER);
                }

                for (int y = yMax - 3; y < yMax; y++)
                {
                    Set(x, y, z, BlockID::GRAVEL);
                }

            }

            for (int y = CAVERN_LEVEL; y < STONE_LEVEL; y++)
            {
                if (Perlin3D(((float)x + m_seed.m_x) * noiseScale, ((float)y + m_seed.m_x) * noiseScale, ((float)z + m_seed.m_x) * noiseScale) > noiseUsed)
                {
                    Set(x, y, z, BlockID::AIR);
                }
            }
        }
    }

    Populate();
}

void World::Populate()
{
    int amountPerChunk = 3;

    for (int Cx = 0; Cx < SUPER_CHUNK_X; Cx++)
    {
        for (int Cz = 0; Cz < SUPER_CHUNK_Z; Cz++)
        {
            if (m_chunks[Cx][Cz] != 0)
            {
                for (int i = 0; i < amountPerChunk; i++)
                {
                    int x = Cx * 16 + rand() % 15;
                    int z = Cz * 16 + rand() % 15;
                    int y;

                    if (x < 2)
                    {
                        x = 2;
                    }
                    if (z < 2)
                    {
                        z = 2;
                    }

                    for (y = PLAIN_LEVEL; GetBlockType(x, y, z) != BlockID::GRASS; y++)
                    {
                        // Increase Y, dont take out this loop
                        if (y > SIZE_CHUNK_Y - 10)
                        {
                            y = -1;
                            break;
                        }
                    }
                    y++;

                    if (y > PLAIN_LEVEL)
                    {
                        CreateTree(x, y, z);
                    }
                }
            }
        }
    }
}

void World::CreateTree(const int x, const int y, const int z)
{
    for (int Tx = x - 2; Tx < x + 2; Tx++)
    {
        for (int Tz = z - 2; Tz < z + 2; Tz++)
        {
            if (GetBlockType(Tx, y, Tz) == BlockID::WOOD)
            {
                return;
            }
        }
    }

    int treeHeight = rand() % 3 + 4;

    int baseLeaves = y + treeHeight - 3;

    BuildLeaves(x, baseLeaves, z);

    for (int height = y; height < y + treeHeight; height++)
    {
        Set(x, height, z, BlockID::WOOD);
    }
}

void World::BuildLeaves(const int x, const int y, const int z)
{
    int layer = 2;
    int repeat = 0;

    for (repeat = y; repeat < y +  3; repeat++)
    {
        if (repeat == y + 2)
        {
            layer -= 1;
        }

        for (int Tx = x - layer; Tx < x + layer + 1; Tx++)
        {
            for (int Tz = z - layer; Tz < z + layer + 1; Tz++)
            {
                if (GetBlockType(Tx, repeat, Tz) <= BlockID::AIR && CHUNK_GENERATE * SIZE_CHUNK_X > Tx && Tx > 0 && CHUNK_GENERATE * SIZE_CHUNK_Z > Tz && Tz > 0)
                {
                    Set(Tx, repeat, Tz, BlockID::LEAVES);
                }
            }
        }
    }

    for (int c = -1; c < 2; c++)
    {
        if (GetBlockType(x, repeat, z + c) == BlockID::AIR)
        {
            Set(x, repeat, z + c, BlockID::LEAVES);
        }

        if (GetBlockType(x + c, repeat, z) == BlockID::AIR)
        {
            Set(x + c, repeat, z, BlockID::LEAVES);
        }

    }
}

BlockID World::GetBlockType(const int x, const int y, const int z)  const
{
    if (x < 0 || y < 0 || z < 0)
    {
        return BlockID::ERROR;
    }

    int cx = x / SIZE_CHUNK_X;
    int cz = z / SIZE_CHUNK_Z;

    if (cx > CHUNK_GENERATE - 1 || cz > CHUNK_GENERATE - 1)
    {
        return BlockID::ERROR;
    }
    else
    {
        return m_chunks[cx][cz]->Get(x % SIZE_CHUNK_X, y, z % SIZE_CHUNK_Z);
    }
}

void World::Set(const int x, const int y, const int z, const BlockID type)
{
    if (x < 0 || y < 0 || z < 0 || x >= SIZE_CHUNK_X * CHUNK_GENERATE || y >= SIZE_CHUNK_Y || z >= SIZE_CHUNK_Z * CHUNK_GENERATE)
    {
        return;
    }

    int cx = x / SIZE_CHUNK_X;
    int cz = z / SIZE_CHUNK_Z;

    if (m_chunks[cx][cz] != nullptr)
    {
        m_chunks[cx][cz]->Set(x % SIZE_CHUNK_X, y, z % SIZE_CHUNK_Z, type);
    }
}

void World::Render()
{
    for (int x = 0; x < SUPER_CHUNK_X; x++)
    {
        for (int z = 0; z < SUPER_CHUNK_Z; z++)
        {
            if (m_chunks[x][z])
            {
                m_chunks[x][z]->m_body.SetTransform(Resources::Transform::Translate(Core::Maths::mat4::Identity(), Core::Maths::vec3((float)x * SIZE_CHUNK_X, 0.f, (float)z * SIZE_CHUNK_Z)));
                m_chunks[x][z]->Render();
            }
        }
    }
    //printf("\nRender:  ");
    m_scene->RenderScene();
}

void World::UpdateBlockArround(const int x, const int y, const int z, const float timer)
{
    m_player.AddBlockToUpdate(x - 1, y, z, timer);
    m_player.AddBlockToUpdate(x + 1, y, z, timer);

    m_player.AddBlockToUpdate(x, y - 1, z, timer);
    m_player.AddBlockToUpdate(x, y + 1, z, timer);

    m_player.AddBlockToUpdate(x, y, z - 1, timer);
    m_player.AddBlockToUpdate(x, y, z + 1, timer);
}

void World::UpdateBlock(const int x, const int y, const int z)
{
    if (x < 0 || y < 0 || z < 0)
    {
        return;
    }

    //if (x > SIZE_CHUNK_X* SUPER_CHUNK_X - 1 || y > SIZE_CHUNK_Y* SUPER_CHUNK_Y  - 1 || z > SIZE_CHUNK_Z* SUPER_CHUNK_Z - 1)
    //{
    //    return;
    //}

    BlockID block = App::GetGameManager().GetWorld().GetBlockType(x, y, z);

    if (block == BlockID::AIR)
    {
        return;
    }

    BlockData& data = App::GetGameManager().MutateBlockDataBase().GetData((BlockID)block);
    
    if (data.m_classType == BlockClassType::SOLID)
    {
        if (data.m_isGravity)
        {
            if (App::GetGameManager().GetWorld().GetBlockType(x, y - 1, z) == BlockID::AIR || App::GetGameManager().GetWorld().GetBlockType(x, y - 1, z) == BlockID::WATER)
            {
                App::GetGameManager().MutateWorld().Set(x, y, z, BlockID::AIR);
                App::GetGameManager().MutateWorld().Set(x, y-1, z, block);

                UpdateBlockArround(x, y, z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)block).m_updateTime);
            }
        }
    }
    else if (data.m_classType == BlockClassType::LIQUID)
    {
        //BlockDataLiquid* dataSolid = (BlockDataLiquid*)data;

        if (App::GetGameManager().GetWorld().GetBlockType(x, y - 1, z) == BlockID::AIR)
        {
            App::GetGameManager().MutateWorld().Set(x, y - 1, z, block);
            UpdateBlockArround(x, y, z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)block).m_updateTime);
        }
        else if(App::GetGameManager().GetWorld().GetBlockType(x, y - 1, z) != BlockID::WATER)
        {
            if (App::GetGameManager().GetWorld().GetBlockType(x + 1, y, z) == BlockID::AIR)
            {
                App::GetGameManager().MutateWorld().Set(x + 1, y, z, block);
                UpdateBlockArround(x, y, z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)block).m_updateTime);
            }
            if (App::GetGameManager().GetWorld().GetBlockType(x - 1, y, z) == BlockID::AIR)
            {
                App::GetGameManager().MutateWorld().Set(x - 1, y, z, block);
                UpdateBlockArround(x, y, z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)block).m_updateTime);
            }
            if (App::GetGameManager().GetWorld().GetBlockType(x, y, z + 1) == BlockID::AIR)
            {
                App::GetGameManager().MutateWorld().Set(x, y, z + 1, block);
                UpdateBlockArround(x, y, z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)block).m_updateTime);
            }
            if (App::GetGameManager().GetWorld().GetBlockType(x, y, z - 1) == BlockID::AIR)
            {
                App::GetGameManager().MutateWorld().Set(x, y, z - 1, block);
                UpdateBlockArround(x, y, z, App::GetGameManager().MutateBlockDataBase().GetData((BlockID)block).m_updateTime);
            }
        }
    }
}
