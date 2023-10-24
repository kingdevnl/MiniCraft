#include <gl/glew.h>
#include <stdexcept>

#include "TextureArray.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.hpp"
#include "spdlog/spdlog.h"


void TextureArray::Create() {
    glGenTextures(1, &m_TextureID);
    glActiveTexture(GL_TEXTURE0 + textureSlotIndex);
    glBindTexture(GL_TEXTURE_2D_ARRAY, m_TextureID);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA, m_ImageSize.x, m_ImageSize.y, 256, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    m_TextureID = textureSlotIndex;
    textureSlotIndex++;
}

void TextureArray::AddTexture(std::string fileName) {
    int width, height, channels;
    unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &channels, STBI_rgb_alpha);
    stbi_set_flip_vertically_on_load(false);
    if(data) {
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, m_ImageIndex, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
        spdlog::info("Loaded texture: {}", fileName);
        m_TextureMap[fileName] = m_ImageIndex;
        m_ImageIndex++;
        return;
    }
    spdlog::critical("Failed to load texture: {}", fileName);
    throw std::runtime_error("Failed to load texture");

}

void TextureArray::Bind() const {

}

int TextureArray::GetTextureIndex(std::string fileName) const {

    //check if not in map
    if(m_TextureMap.find(fileName) == m_TextureMap.end()) {
        spdlog::critical("Texture not found: {}", fileName);
        throw std::runtime_error("Texture not found");
    }

    return m_TextureMap.at(fileName);
}

bool TextureArray::TextureExists(std::string fileName) const {
    return m_TextureMap.find(fileName) != m_TextureMap.end();
}

