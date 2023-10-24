#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include "engine/Types.hpp"
#include "game/Block.hpp"
#define CHUNK_SIZE  16

namespace std {
    template<>
    struct hash<glm::vec3> {
        std::size_t operator()(const glm::vec3 &v) const {
            std::size_t seed = 0;
            // Combine the hashes of the vector's components
            seed ^= std::hash<float>{}(v.x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<float>{}(v.y) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            seed ^= std::hash<float>{}(v.z) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            return seed;
        }
    };
}


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
