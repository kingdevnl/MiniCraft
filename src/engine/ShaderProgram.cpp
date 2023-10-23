#include <gl/glew.h>
#include <spdlog/spdlog.h>
#include "ShaderProgram.hpp"

ShaderProgram::ShaderProgram(std::string vertexSource, std::string fragmentSource)
    : m_VertexSource(vertexSource), m_FragmentSource(fragmentSource)
{

}

void ShaderProgram::Create() {
    m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
    m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    const char* vertexSource = m_VertexSource.c_str();
    const char* fragmentSource = m_FragmentSource.c_str();

    glShaderSource(m_VertexShader, 1, &vertexSource, nullptr);
    glShaderSource(m_FragmentShader, 1, &fragmentSource, nullptr);

    glCompileShader(m_VertexShader);

    int result;
    glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(m_VertexShader, 512, nullptr, infoLog);
        spdlog::critical("Failed to compile vertex shader: {}", infoLog);
        throw std::runtime_error("Failed to compile vertex shader!");
    }

    glCompileShader(m_FragmentShader);

    glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &result);

    if(result == GL_FALSE) {
        char infoLog[512];
        glGetShaderInfoLog(m_FragmentShader, 512, nullptr, infoLog);
        spdlog::critical("Failed to compile fragment shader: {}", infoLog);
        throw std::runtime_error("Failed to compile fragment shader!");
    }

    m_Program = glCreateProgram();

    glAttachShader(m_Program, m_VertexShader);
    glAttachShader(m_Program, m_FragmentShader);
    glLinkProgram(m_Program);

}

ShaderProgram::~ShaderProgram() {
    glDetachShader(m_Program, m_VertexShader);
    glDetachShader(m_Program, m_FragmentShader);
    glDeleteShader(m_VertexShader);
    glDeleteShader(m_FragmentShader);
    glDeleteProgram(m_Program);
}

Ref<ShaderProgram> ShaderProgram::FromFile(std::string vertexPath, std::string fragmentPath) {
    return Ref<ShaderProgram>();
}

void ShaderProgram::Bind() {
    glUseProgram(m_Program);
}

void ShaderProgram::Unbind() {
    glUseProgram(0);
}
