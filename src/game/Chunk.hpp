#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include "engine/Types.hpp"
#include "engine/vec3hash.hpp"
#include "game/Block.hpp"
#include "game/Vertex.hpp"


#define CHUNK_SIZE  16

class ShaderProgram;


class Chunk {
public:
    Chunk(glm::vec3 mChunkPos);
    void Generate();
    void BuildMesh();


    void Render(Ref<ShaderProgram> shaderProgram);

    Block GetBlockAt(glm::vec3 pos);


    inline glm::vec3 GetChunkPos() const { return m_ChunkPos; }
    inline void SetIsDirty(bool isDirty) { m_IsDirty = isDirty; }



private:
    glm::vec3 m_ChunkPos;
    std::unordered_map<glm::vec3, Block> m_Blocks;
    uint m_VAO, m_VBO;
    int m_VertexCount = 0;
    bool m_IsDirty = false;
    std::vector<Vertex> m_Vertices;


    void CreateVAO();
};
