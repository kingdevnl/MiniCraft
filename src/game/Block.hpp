#pragma once
#include "glm/glm.hpp"

struct BlockInfo;

struct Block {
    BlockInfo* blockInfo;
    glm::vec3 position;
};