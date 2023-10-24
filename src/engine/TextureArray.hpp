#pragma once
#include <string>
#include <glm/glm.hpp>
#include <unordered_map>
#include "engine/Types.hpp"


class TextureArray {

public:
    void Create();

    void AddTexture(std::string fileName);
    void Bind() const;

    inline uint GetTextureID() const { return m_TextureID; }

    [[nodiscard]] int GetTextureIndex(std::string fileName) const;

    bool TextureExists(std::string fileName) const;


private:
    uint m_TextureID;
    glm::vec2 m_ImageSize = glm::vec2(160, 160);
    uint m_ImageIndex = 0;
    std::unordered_map<std::string, uint> m_TextureMap;
};
inline uint textureSlotIndex = 0;