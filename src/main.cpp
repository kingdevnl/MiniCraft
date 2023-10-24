#include <spdlog/spdlog.h>
#include "MiniCraft.hpp"

int main() {
    spdlog::info("Hello, World!");





    try {
        MiniCraft::m_Instance = CreateRef<MiniCraft>();

        MiniCraft::m_Instance->Init();
        MiniCraft::m_Instance->Run();
    } catch (std::exception &e) {
        spdlog::critical("{}", e.what());
    }


    return 0;
}
