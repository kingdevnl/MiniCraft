#include <gl/glew.h>
#include "MiniCraft.hpp"
#include "engine/Window.hpp"
#include "engine/ShaderProgram.hpp"

MiniCraft::MiniCraft() {
    this->m_Window =CreateRef<Window>(800, 600, "MiniCraft");


    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(0.0, 0.0, 1.0, 1.0);
        }
    )";

    this->m_Shader = CreateRef<ShaderProgram>(vertexShaderSource, fragmentShaderSource);

}


void MiniCraft::Init() {
    m_Window->Create();
    m_Shader->Create();
}

void MiniCraft::Run() {
    while (!m_Window->ShouldClose()) {
        m_Window->Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader->Bind();
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        glRotatef(0.1f, 0.0f, 0.0f, 1.0f);

    }
}


std::shared_ptr<MiniCraft> MiniCraft::m_Instance = nullptr;

