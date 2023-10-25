#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "game/Vertex.hpp"
#include "BlockRegistry.hpp"
#include "Chunk.hpp"

enum EnumFace : uint8_t {
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    TOP = 4,
    BOTTOM = 5
};


namespace BlockFace {
    float scale = 0.5f;
    static std::vector<glm::vec4> FRONT = {
            glm::vec4(-scale, scale, scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(-scale, scale, scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
    };

    static std::vector<glm::vec4> UVS = {
            glm::vec4(0.0, 0.0, 0.0, 0.0),
            glm::vec4(0.0, 1.0, 0.0, 0.0),
            glm::vec4(1.0, 1.0, 0.0, 0.0),
            glm::vec4(0.0, 0.0, 0.0, 0.0),
            glm::vec4(1.0, 1.0, 0.0, 0.0),
            glm::vec4(1.0, 0.0, 0.0, 0.0),
    };


    static std::vector<glm::vec4> BACK = {
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
            glm::vec4(scale, scale, -scale, 1.0),
    };

    static std::vector<glm::vec4> LEFT = {
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(-scale, scale, scale, 1.0),
    };
    static std::vector<glm::vec4> RIGHT = {
            glm::vec4(scale, scale, -scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, scale, -scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
    };

    static std::vector<glm::vec4> TOP = {
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, scale, scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
            glm::vec4(scale, scale, -scale, 1.0),
    };
    static std::vector<glm::vec4> BOTTOM = {
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
    };

    inline std::vector<Vertex> GetVert(EnumFace face, Chunk* chunk, Block block, float texID) {
        std::vector<Vertex> verts;
        glm::vec4 normal;
        const std::vector<glm::vec4> *vertexArray = nullptr;


        auto chunkPos = chunk->GetChunkPos();

        switch (face) {
            case EnumFace::FRONT:
                normal = glm::vec4(0.0, 0.0, 1.0, 0.0);
                vertexArray = &FRONT;
                break;
            case EnumFace::BACK:
                normal = glm::vec4(0.0, 0.0, -1.0, 0.0);
                vertexArray = &BACK;
                break;
            case EnumFace::LEFT:
                normal = glm::vec4(-1.0, 0.0, 0.0, 0.0);
                vertexArray = &LEFT;
                break;
            case EnumFace::RIGHT:
                normal = glm::vec4(1.0, 0.0, 0.0, 0.0);
                vertexArray = &RIGHT;
                break;
            case EnumFace::TOP:
                normal = glm::vec4(0.0, 1.0, 0.0, 0.0);
                vertexArray = &TOP;
                break;
            case EnumFace::BOTTOM:
                normal = glm::vec4(0.0, -1.0, 0.0, 0.0);
                vertexArray = &BOTTOM;
                break;
            default:
                // Handle other faces or invalid input if needed
                break;
        }




        glm::vec4 chunkOffset = {
                chunkPos.x * CHUNK_SIZE + block.position.x,
                chunkPos.y * CHUNK_SIZE + block.position.y,
                chunkPos.z * CHUNK_SIZE + block.position.z,
                1.0,
        };

        if (vertexArray) {
            int i = 0;
            for (const auto &vert: *vertexArray) {
                // Assuming 'i' comes from somewhere
                glm::vec4 uv = UVS[i];
                verts.push_back(Vertex{texID, vert + chunkOffset, normal, uv});
                i++;
            }
        }

        return verts;

    }
}