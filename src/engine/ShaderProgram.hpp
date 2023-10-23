#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include "engine/Types.hpp"


class ShaderProgram {
public:
    ShaderProgram(std::string vertexSource, std::string fragmentSource);
    ~ShaderProgram();
    void Create();

    void Bind();
    void Unbind();

    void SetUniform(std::string name, float value);
    void SetUniform(std::string name, glm::vec2 value);
    void SetUniform(std::string name, glm::vec3 value);
    void SetUniform(std::string name, glm::vec4 value);
    void SetUniform(std::string name, glm::mat4 value);


private:
    uint m_Program;

    std::string m_VertexSource;
    std::string m_FragmentSource;

    uint m_VertexShader;
    uint m_FragmentShader;
    std::unordered_map<std::string, int> m_UniformLocations;
    int GetUniformLocation(std::string& name);

public:
    static Ref<ShaderProgram> FromFile(std::string vertexPath, std::string fragmentPath);
};
