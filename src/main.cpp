#include <spdlog/spdlog.h>
#include "MiniCraft.hpp"

int main() {
    spdlog::info("Hello, World!");

    MiniCraft::m_Instance = CreateRef<MiniCraft>();

    MiniCraft::m_Instance->Init();
    MiniCraft::m_Instance->Run();

    return 0;
}
