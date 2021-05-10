#pragma once

#include "ResourceGFX.h" 
#include "Resources/Scene.h"
#include "Resources/LightManager.h"
#include "Resources/Shader.h"
#include "BlockID.h"

#define SIZE_CHUNK_X 16
#define SIZE_CHUNK_Y 256
#define SIZE_CHUNK_Z 16

#define TEXTURE_WIDTH 20
#define TEXTURE_HEIGHT 8

class Chunk
{
public:
    Chunk();
    Chunk(const Chunk& other) = delete;
    Chunk& operator=(const Chunk& other) = delete;
    ~Chunk() = default;

    BlockID Get(const int x, const int y, const int z) const;
    void Set(const int x, const int y, const int z, const BlockID type);

    void Init();
    void Update();
    void Render();

    bool BlockOnSide(const int x, const int y, const int z, const int type);


#pragma warning(push)
#pragma warning(disable:4251)
    std::vector<float> m_data;
#pragma warning(pop)

    int m_blocks[SIZE_CHUNK_X][SIZE_CHUNK_Y][SIZE_CHUNK_Z]{ 0 };
    bool m_isModif = true;

    Resources::Mesh m_mesh;
    LowRenderer::Model m_model;
    Core::DataStructure::Graph m_body;
    unsigned int m_texture;

    bool m_firstTime = true;

};