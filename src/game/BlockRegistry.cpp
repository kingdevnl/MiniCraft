#include <fstream>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>
#include "game/BlockRegistry.hpp"
#include "engine/TextureArray.hpp"

BlockRegistry::BlockRegistry(const Ref<TextureArray> &mTextureArray) : m_TextureArray(mTextureArray) {}


float hash(std::string str) {
    float hash = 0;
    for (int i = 0; i < str.length(); i++) {
        hash += str[i] * i * 73856093 ^ i * 19349663 ^ i * 83492791;
    }
    return abs(hash);
}


void BlockRegistry::LoadFromFile(std::string path) {
    //read assets/blocks.json
    std::ifstream i("assets/blocks.json");
    nlohmann::json j;
    i >> j;

    //get all keys in root
    for (auto &element: j.items()) {
        std::string blockKey = element.key();
        auto blockObject = element.value();

        auto *blockInfo = new BlockInfo();
        blockInfo->name = blockKey;

        if(blockObject.contains("id")) {
            blockInfo->id = blockObject["id"];
        } else {
            blockInfo->id = hash(blockKey);
        }

        blockInfo->textures.side = blockObject["textures"]["side"];
        blockInfo->textures.top = blockObject["textures"]["top"];

        m_Blocks[blockKey] = blockInfo;

        if (!m_TextureArray->TextureExists(blockInfo->textures.side)) {
            m_TextureArray->AddTexture(blockInfo->textures.side);
        }
        if (!m_TextureArray->TextureExists(blockInfo->textures.top)) {
            m_TextureArray->AddTexture(blockInfo->textures.top);
        }


        spdlog::info("BlockRegistry: Loaded block {}:{}", blockKey, blockInfo->id);
    }


}

BlockInfo *BlockRegistry::GetBlockInfo(std::string name) {
    //check if block exists
    if (m_Blocks.find(name) == m_Blocks.end()) {
        spdlog::critical("BlockRegistry: Block {} does not exist!", name);
        return nullptr;
    }

    return m_Blocks[name];
}

