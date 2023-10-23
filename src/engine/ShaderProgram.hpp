#pragma once
#include <string>
#include "engine/Types.hpp"

class ShaderProgram {
public:
    ShaderProgram(std::string vertexSource, std::string fragmentSource);
    ~ShaderProgram();
    void Create();

    void Bind();
    void Unbind();

private:
    uint m_Program;

    std::string m_VertexSource;
    std::string m_FragmentSource;

    uint m_VertexShader;
    uint m_FragmentShader;

public:
    static Ref<ShaderProgram> FromFile(std::string vertexPath, std::string fragmentPath);
};
