#include <gl/glew.h>
#include "MiniCraft.hpp"
#include "engine/TextureArray.hpp"
#include "game/Chunk.hpp"
#include "game/BlockRegistry.hpp"
#include "game/Vertex.hpp"
#include "game/BlockFace.hpp"

Chunk::Chunk(glm::vec3 mChunkPos) : m_ChunkPos(mChunkPos) {}

void Chunk::Generate() {
    auto blockRegistry = MiniCraft::Get()->GetBlockRegistry();
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            for (int y = 0; y < CHUNK_SIZE; y++) {
                glm::vec3 pos = glm::vec3(x, y, z);

                //if y is top make it grass else dirt
                if (pos.y == CHUNK_SIZE - 1) {
                    auto blockInfo = blockRegistry->GetBlockInfo("grass");
                    m_Blocks[pos] = Block{blockInfo, pos};
                    continue;
                }

                auto blockInfo = blockRegistry->GetBlockInfo("dirt");
                m_Blocks[pos] = Block{blockInfo, pos};
            }
        }
    }
}

void Chunk::BuildMesh() {
    auto textureArray = MiniCraft::Get()->GetTextureArray();
    std::vector<Vertex> vertices;

    for(auto& pair : m_Blocks) {
        auto block = pair.second;

        auto addFace = [&](EnumFace face, float texID) {
            auto v = BlockFace::GetVert(face, this, block, texID);
            vertices.insert(vertices.end(), v.begin(), v.end());
        };



        if (GetBlockAt(block.position + glm::vec3(0, 0, 1)).blockInfo->id == 0) {
            addFace(EnumFace::FRONT, (float)textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(0, 0, -1)).blockInfo->id == 0) {
            addFace(EnumFace::BACK, (float)textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(-1, 0, 0)).blockInfo->id == 0) {
            addFace(EnumFace::LEFT, (float)textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(1, 0, 0)).blockInfo->id == 0) {
            addFace(EnumFace::RIGHT, (float)textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }
        if (GetBlockAt(block.position + glm::vec3(0, 1, 0)).blockInfo->id == 0) {
            addFace(EnumFace::TOP, (float)textureArray->GetTextureIndex(block.blockInfo->textures.top));
        }
        if (GetBlockAt(block.position + glm::vec3(0, -1, 0)).blockInfo->id == 0) {
            addFace(EnumFace::BOTTOM, (float)textureArray->GetTextureIndex(block.blockInfo->textures.side));
        }

    }

    this->m_VertexCount = vertices.size();

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);



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

}

Block Chunk::GetBlockAt(glm::vec3 pos) {
    //check if block exists
    if (m_Blocks.find(pos) == m_Blocks.end()) {
        auto* info = new BlockInfo();
        info->id = 0;
        return Block{info, pos};
    }
    return m_Blocks[pos];
}

void Chunk::Render(Ref<ShaderProgram> shaderProgram) {
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, m_VertexCount);
    glBindVertexArray(0);
}
