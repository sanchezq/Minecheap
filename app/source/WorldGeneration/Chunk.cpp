#include "Chunk.h"
#include <App.h>
#include "GameManager.h"
#include "BlockID.h"
#include "Resources/ResourcesManager.h"

Chunk::Chunk()
{
    m_data.reserve(SIZE_CHUNK_X * SIZE_CHUNK_Y * SIZE_CHUNK_Z * 6 * 6); //block * face * vertex
    m_texture = Resources::ResourcesManager::GetTexture("resources/Images/Blocks/MegaTexture.png");
}

BlockID Chunk::Get(const int x, const int y, const int z) const
{
    return (BlockID)m_blocks[x][y][z];
}

void Chunk::Set(const int x, const int y, const int z, const BlockID type)
{
    m_blocks[x][y][z] = (int)type;
    m_isModif = true;
}

void Chunk::Init()
{
    m_isModif = false;

    m_data.resize(0);

    float   blockTextX = 1.f / TEXTURE_WIDTH,
        blockTextY = 1.f / TEXTURE_HEIGHT;

    float textU0, textU1, textV0, textV1;

    for (float x = 0; x < SIZE_CHUNK_X; x++)
    {
        for (float y = 0; y < SIZE_CHUNK_Y; y++)
        {
            for (float z = 0; z < SIZE_CHUNK_Z; z++)
            {
                int type = m_blocks[(int)x][(int)y][(int)z];

                // Empty block?
                if (type == 0)
                    continue;

                // 0,1 /------\ 1,1
                //     |      |
                //     |      |
                // 0,0 \------/ 1,0

                textU0 = blockTextX * type; textU1 = textU0 + blockTextX;
                textV1 = 1.f; textV0 = textV1 - blockTextY;

                // TOP
                if (y == SIZE_CHUNK_Y - 1 || BlockOnSide((int)x, (int)y + 1, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU0, textV0,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU1, textV0,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU0, textV1,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU1, textV0,
                            x + 1, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU1, textV1,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU0, textV1});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // FRONT
                if (x == 0 || BlockOnSide((int)x - 1, (int)y, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU0, textV0,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU1, textV0,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU0, textV1,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU0, textV1,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU1, textV0,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU1, textV1});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // LEFT
                if (z == 0 || BlockOnSide((int)x, (int)y, (int)z - 1, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU1, textV0,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU1, textV1,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU0, textV0,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU0, textV0,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU1, textV1,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU0, textV1});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // RIGHT
                if (z == SIZE_CHUNK_Z - 1 || BlockOnSide((int)x, (int)y, (int)z + 1, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU0, textV0,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU1, textV0,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU0, textV1,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU1, textV0,
                            x + 1, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU1, textV1,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU0, textV1 });
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // BEHIND
                if (x == SIZE_CHUNK_X - 1 || BlockOnSide((int)x + 1, (int)y, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x + 1, y, z, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU1, textV0,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU1, textV1,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU0, textV0,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU1, textV1,
                            x + 1, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU0, textV1,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU0, textV0});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // BOT
                if (y == 0 || BlockOnSide((int)x, (int)y - 1, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU0, textV1,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU0, textV0,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU1, textV1,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU1, textV1,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU0, textV0,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU1, textV0});
                }
            }
        }
    }

    Core::Maths::mat4 mat = m_body.GetTransform();
    m_body.~Graph();

    m_mesh.SetData(m_data);
    m_model = LowRenderer::Model(m_data);
    m_model.SetTextureID(m_texture);
    m_body = Core::DataStructure::Graph(&m_model, sqrtf(128.f), Core::Maths::vec3{ 8.f, 128.f, 8.f }, Core::Maths::vec4{ 1.f, 0.f, 0.f, 1.f }); // Red !
    // (16/2)^2 + (16/2)^2
    m_body.SetTransform(mat);

    m_model.ModifData(m_data);
}

void Chunk::Update()
{
    m_isModif = false;

    m_data.resize(0);

    float   blockTextX = 1.f / TEXTURE_WIDTH,
        blockTextY = 1.f / TEXTURE_HEIGHT;

    float textU0, textU1, textV0, textV1;

    for (float x = 0; x < SIZE_CHUNK_X; x++)
    {
        for (float y = 0; y < SIZE_CHUNK_Y; y++)
        {
            for (float z = 0; z < SIZE_CHUNK_Z; z++)
            {
                int type = m_blocks[(int)x][(int)y][(int)z];

                // Empty block?
                if (type == 0)
                    continue;

                // 0,1 /------\ 1,1
                //     |      |
                //     |      |
                // 0,0 \------/ 1,0

                textU0 = blockTextX * type; textU1 = textU0 + blockTextX;
                textV1 = 1.f; textV0 = textV1 - blockTextY;

                // TOP
                if (y == SIZE_CHUNK_Y - 1 || BlockOnSide((int)x, (int)y + 1, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU0, textV0,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU1, textV0,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU0, textV1,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU1, textV0,
                            x + 1, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU1, textV1,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 0.f, -1.0f, textU0, textV1});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // FRONT
                if (x == 0 || BlockOnSide((int)x - 1, (int)y, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU0, textV0,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU1, textV0,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU0, textV1,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU0, textV1,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU1, textV0,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, -1.0f, 0.f, 0.f, textU1, textV1});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // LEFT
                if (z == 0 || BlockOnSide((int)x, (int)y, (int)z - 1, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU1, textV0,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU1, textV1,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU0, textV0,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU0, textV0,
                            x, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU1, textV1,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, -1.0f, 0.f, textU0, textV1});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // RIGHT
                if (z == SIZE_CHUNK_Z - 1 || BlockOnSide((int)x, (int)y, (int)z + 1, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU0, textV0,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU1, textV0,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU0, textV1,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU1, textV0,
                            x + 1, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU1, textV1,
                            x, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 0.f, 1.0f, textU0, textV1 });
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // BEHIND
                if (x == SIZE_CHUNK_X - 1 || BlockOnSide((int)x + 1, (int)y, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x + 1, y, z, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU1, textV0,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU1, textV1,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU0, textV0,
                            x + 1, y + 1, z, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU1, textV1,
                            x + 1, y + 1, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU0, textV1,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 0.f, 1.0f, 0.f, textU0, textV0});
                }

                textV1 -= blockTextY; textV0 -= blockTextY;
                // BOT
                if (y == 0 || BlockOnSide((int)x, (int)y - 1, (int)z, type))
                {
                    m_data.insert(m_data.end(), std::initializer_list<float>{
                        x, y, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU0, textV1,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU0, textV0,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU1, textV1,
                            x, y, z + 1, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU1, textV1,
                            x + 1, y, z, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU0, textV0,
                            x + 1, y, z + 1, 1.0f, 1.0f, 1.0f, 1.0f, 0.f, 0.f, textU1, textV0});
                }
            }
        }
    }

    Core::Maths::mat4 mat = m_body.GetTransform();
    m_body.~Graph();

    m_mesh.SetData(m_data);
    m_model.SetTextureID(m_texture);
    m_body = Core::DataStructure::Graph(&m_model, sqrtf(128.f), Core::Maths::vec3{ 8.f, 128.f, 8.f }, Core::Maths::vec4{ 1.f, 0.f, 0.f, 1.f }); // Red !
    // (16/2)^2 + (16/2)^2
    m_body.SetTransform(mat);

    m_model.ModifData(m_data);
}

void Chunk::Render()
{
    if (m_isModif)
    {
        Update();
    }
}

bool Chunk::BlockOnSide(const int x, const int y, const int z, const int type)
{
    if (m_blocks[x][y][z] == 0)
    {
        return true;
    }

    if (type != static_cast<int>(BlockID::WATER) && m_blocks[x][y][z] == static_cast<int>(BlockID::WATER))
    {
        return true;
    }

    if (App::GetGameManager().m_cameraSettings.m_transparency)
    {
        if (m_blocks[x][y][z] == static_cast<int>(BlockID::LEAVES))
        {
            return true;
        }
    }

    return false;
}
