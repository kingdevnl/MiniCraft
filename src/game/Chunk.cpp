#include <gl/glew.h>
#include "game/Chunk.hpp"
#include "MiniCraft.hpp"
#include "engine/TextureArray.hpp"
#include "game/BlockRegistry.hpp"
#include "game/BlockFace.hpp"
#include "vendor/FastNoiseLite.hpp"

Chunk::Chunk(glm::vec3 mChunkPos) : m_ChunkPos(mChunkPos) {}

//simple hash function for 3 numbers
int hash(int x, int y, int z) {
    return x * 73856093 ^ y * 19349663 ^ z * 83492791;
}


void Chunk::Generate() {

    int seed = 1337;

    FastNoiseLite terrain;
    terrain.SetSeed(seed);
    terrain.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    terrain.SetFrequency(0.001f);

    FastNoiseLite forest;
    forest.SetSeed(seed);
    forest.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    forest.SetFractalType(FastNoiseLite::FractalType_Ridged);


    FastNoiseLite mountain;
    mountain.SetSeed(seed);
    mountain.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    mountain.SetFractalType(FastNoiseLite::FractalType_Ridged);
    mountain.SetFrequency(0.005f);


    FastNoiseLite river;
    river.SetSeed(seed);
    river.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    river.SetFractalType(FastNoiseLite::FractalType_Ridged);
    river.SetFrequency(0.001f);



    auto getHeight = [&](float x, float z) {
        int height;

        float noise = abs(terrain.GetNoise(x, z) + 0.5f);
        if (noise < 0.05f)
        {
            height = (int)abs(8 * (river.GetNoise(x, z) + 0.8f)) + 30;
        }

        else if (noise < 1.2f)
        {
            height = (int)abs(10 * (forest.GetNoise(x, z) + 0.8f)) + 30;
        }

        else
        {
            height = (int)abs(30 * (mountain.GetNoise(x, z) + 0.8f)) + 30;
        }

        return height;
    };


    auto blockRegistry = MiniCraft::Get()->GetBlockRegistry();
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {

            int height = getHeight(x + m_ChunkPos.x * CHUNK_SIZE, z + m_ChunkPos.z * CHUNK_SIZE);

            for (int y = 0; y < height; y++) {
                glm::vec4 pos = glm::vec4(x, y, z, 1.0);
                //if top layer use grass
                BlockInfo* blockInfo;
                if (y == height - 1) {
                    blockInfo = blockRegistry->GetBlockInfo("grass");
                } else if (y > height - 5) {
                    blockInfo = blockRegistry->GetBlockInfo("dirt");
                } else if (y == 0) {
                    blockInfo = blockRegistry->GetBlockInfo("bedrock");
                }
                else {
                    blockInfo = blockRegistry->GetBlockInfo("cobblestone");
                }

                m_Blocks[pos] = Block{blockInfo, pos};

            }

        }
    }
}

void Chunk::BuildMesh() {
    auto textureArray = MiniCraft::Get()->GetTextureArray();


    for (auto &[k, block]: m_Blocks) {
        auto addFace = [&](EnumFace face, float texID) {
            auto v = BlockFace::GetVert(face, this, block, texID);
            m_Vertices.insert(m_Vertices.end(), v.begin(), v.end());
        };


        if (GetBlockAt(block.position + glm::vec3(0, 0, 1)).blockInfo->id == 0) {
            addFace(EnumFace::FRONT, (float) textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(0, 0, -1)).blockInfo->id == 0) {
            addFace(EnumFace::BACK, (float) textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(-1, 0, 0)).blockInfo->id == 0) {
            addFace(EnumFace::LEFT, (float) textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(1, 0, 0)).blockInfo->id == 0) {
            addFace(EnumFace::RIGHT, (float) textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(0, 1, 0)).blockInfo->id == 0) {
            addFace(EnumFace::TOP, (float) textureArray->GetTextureIndex(block.blockInfo->textures.top));
        }
        if (GetBlockAt(block.position + glm::vec3(0, -1, 0)).blockInfo->id == 0) {
            addFace(EnumFace::BOTTOM, (float) textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }

    }

    this->m_VertexCount = m_Vertices.size();

    SetIsDirty(true);



}

Block Chunk::GetBlockAt(glm::vec3 pos) {
    //check if block exists
    if (m_Blocks.find(pos) == m_Blocks.end()) {
        auto *info = new BlockInfo();
        info->id = 0;
        return Block{info, pos};
    }
    return m_Blocks[pos];
}

void Chunk::Render(Ref<ShaderProgram> shaderProgram) {

    if(m_IsDirty) {
        CreateVAO();
    }

    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
    glBindVertexArray(0);
}

void Chunk::CreateVAO() {
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), m_Vertices.data(), GL_STATIC_DRAW);



    // Block ID
    glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, blockID));
    glEnableVertexAttribArray(0);


    // Position
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));
    glEnableVertexAttribArray(1);

    // Normal
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);

    // UV
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, uv));
    glEnableVertexAttribArray(3);


    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    SetIsDirty(false);
}
