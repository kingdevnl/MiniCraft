#pragma once
#include <glm/glm.hpp>

extern "C" struct Vertex {
    float blockID;
    glm::vec4 position;
    glm::vec4 normal;
    glm::vec4 uv;
};