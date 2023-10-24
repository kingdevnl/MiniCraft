#pragma once
#include <string>
#include <unordered_map>
#include "engine/Types.hpp"
class TextureArray;

struct BlockTextures {
    std::string side;
    std::string top;
};

struct BlockInfo {
    std::string name;
    float id;
    BlockTextures textures;
};

class BlockRegistry {

public:
    explicit BlockRegistry(const Ref<TextureArray> &mTextureArray);

    void LoadFromFile(std::string path);

    BlockInfo* GetBlockInfo(std::string name);

private:
    Ref<TextureArray> m_TextureArray;
    std::unordered_map<std::string, BlockInfo*> m_Blocks;

};


