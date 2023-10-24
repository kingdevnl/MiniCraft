#include <gl/glew.h>
#include <spdlog/spdlog.h>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.hpp"
#include "engine/io.hpp"

ShaderProgram::ShaderProgram(std::string vertexSource, std::string fragmentSource)
        : m_VertexSource(vertexSource), m_FragmentSource(fragmentSource) {

}

void ShaderProgram::Create() {
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char *vertexSource = m_VertexSource.c_str();
    const char *fragmentSource = m_FragmentSource.c_str();

    glShaderSource(m_VertexShader, 1, &vertexSource, nullptr);
    glShaderSource(m_FragmentShader, 1, &fragmentSource, nullptr);

    glCompileShader(m_VertexShader);

    int result;
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &result);

    spdlog::info("Compiling vertex shader: {}", result);

    if (result == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(m_VertexShader, 512, nullptr, infoLog);
        spdlog::critical("Failed to compile vertex shader: {}", infoLog);
        throw std::runtime_error("Failed to compile vertex shader!");
    }

    glCompileShader(m_FragmentShader);

    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(m_FragmentShader, 512, nullptr, infoLog);
        spdlog::critical("Failed to compile fragment shader: {}", infoLog);
        throw std::runtime_error("Failed to compile fragment shader!");
    }

    m_Program = glCreateProgram();

    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);
    glLinkProgram(m_Program);

    glGetProgramiv(m_Program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE) {
        char infoLog[512];
        glGetProgramInfoLog(m_Program, 512, nullptr, infoLog);
        spdlog::critical("Failed to link shader program: {}", infoLog);
        throw std::runtime_error("Failed to link shader program!");
    }

}

ShaderProgram::~ShaderProgram() {
    glDetachShader(m_Program, m_VertexShader);
    glDetachShader(m_Program, m_FragmentShader);
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
    glDeleteProgram(m_Program);
}

Ref<ShaderProgram> ShaderProgram::FromFile(std::string vertexPath, std::string fragmentPath) {
    std::string vs = IO::ReadFile(std::move(vertexPath));
    std::string fs = IO::ReadFile(std::move(fragmentPath));
    return CreateRef<ShaderProgram>(vs, fs);
}

void ShaderProgram::Bind() {
    glUseProgram(m_Program);
}

void ShaderProgram::Unbind() {
    glUseProgram(0);
}

void ShaderProgram::SetUniform1i(std::string name, int value) {
    glUniform1i(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(std::string name, float value) {
    glUniform1f(GetUniformLocation(name), value);
}

void ShaderProgram::SetUniform(std::string name, glm::vec2 value) {
    glUniform2f(GetUniformLocation(name), value.x, value.y);
}

void ShaderProgram::SetUniform(std::string name, glm::vec3 value) {
    glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
}

void ShaderProgram::SetUniform(std::string name, glm::vec4 value) {
    glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
}

void ShaderProgram::SetUniform(std::string name, glm::mat4 value) {
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

int ShaderProgram::GetUniformLocation(std::string& name) {

    if (m_UniformLocations.find(name) != m_UniformLocations.end()) {
        return m_UniformLocations[name];
    }

    int loc = glGetUniformLocation(m_Program, name.c_str());
    if (loc == -1) {
        spdlog::critical("Uniform '{}' not found!", name);
        throw std::runtime_error("Uniform not found!");
    }
    m_UniformLocations[name] = loc;
    return loc;
}
