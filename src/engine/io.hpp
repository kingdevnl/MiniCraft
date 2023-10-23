#pragma once

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <string>
#include <spdlog/spdlog.h>


namespace IO {
    std::string ReadFile(std::string path) {
        std::string code;
        std::ifstream file;
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try {
            file.open(path);
            std::stringstream stream;
            stream << file.rdbuf();
            file.close();
            code = stream.str();
        } catch (std::ifstream::failure e) {
            spdlog::critical("Failed to read file: {}", path);
            throw std::runtime_error("Failed to read file!");
        }
        return code;
    }
}