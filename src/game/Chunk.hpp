#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include "engine/Types.hpp"
#include "game/Block.hpp"
#include "engine/vec3hash.hpp"

#define CHUNK_SIZE  16

class ShaderProgram;


class Chunk {
public:
    Chunk(glm::vec3 mChunkPos);
    void Generate();
    void BuildMesh();


    void Render(Ref<ShaderProgram> shaderProgram);


    inline glm::vec3 GetChunkPos() const { return m_ChunkPos; }
    Block GetBlockAt(glm::vec3 pos);

private:
    glm::vec3 m_ChunkPos;
    std::unordered_map<glm::vec3, Block> m_Blocks;
    uint m_VAO, m_VBO;
    int m_VertexCount = 0;
};
