#include <vector>
#include <spdlog/spdlog.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "MiniCraft.hpp"
#include "engine/Window.hpp"
#include "engine/Camera.hpp"
#include "engine/ShaderProgram.hpp"



extern "C" struct Vertex {
    glm::vec4 position;
    glm::vec4 color;
    glm::vec4 normal;
};

enum EnumFace: uint8_t {
    FRONT = 0,
    BACK = 1,
    LEFT = 2,
    RIGHT = 3,
    TOP = 4,
    BOTTOM = 5
};



namespace faces {
    float scale = 0.5f;
    static std::vector<glm::vec4> FRONT = {
            glm::vec4(-scale, scale, scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(-scale, scale, scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
    };
    static std::vector<glm::vec4> BACK = {
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
            glm::vec4(scale, scale, -scale, 1.0),
    };

    static std::vector<glm::vec4> LEFT = {
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(-scale, scale, scale, 1.0),
    };
    static std::vector<glm::vec4> RIGHT = {
            glm::vec4(scale, scale, -scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, scale, -scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
    };

    static std::vector<glm::vec4> TOP = {
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(-scale, scale, scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
            glm::vec4(-scale, scale, -scale, 1.0),
            glm::vec4(scale, scale, scale, 1.0),
            glm::vec4(scale, scale, -scale, 1.0),
    };
    static std::vector<glm::vec4> BOTTOM = {
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(-scale, -scale, scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(-scale, -scale, -scale, 1.0),
            glm::vec4(scale, -scale, scale, 1.0),
            glm::vec4(scale, -scale, -scale, 1.0),
    };
    std::vector<Vertex> GetVerts(EnumFace face, glm::vec4 color) {
        std::vector<Vertex> verts;





        if(face == EnumFace::FRONT) {
            for(auto& vert: FRONT) {
                glm::vec4 normal = glm::vec4(0.0, 0.0, 1.0, 0.0);
                verts.push_back(Vertex{vert, color, normal});
            }
        }
        if(face == EnumFace::BACK) {
            for(auto& vert: BACK) {
                glm::vec4 normal = glm::vec4(0.0, 0.0, -1.0, 0.0);
                verts.push_back(Vertex{vert, color, normal});
            }
        }

        if (face == EnumFace::LEFT) {
            for(auto& vert: LEFT) {
                glm::vec4 normal = glm::vec4(-1.0, 0.0, 0.0, 0.0);
                verts.push_back(Vertex{vert, color, normal});
            }
        }
        if (face == EnumFace::RIGHT) {
            for(auto& vert: RIGHT) {
                glm::vec4 normal = glm::vec4(1.0, 0.0, 0.0, 0.0);
                verts.push_back(Vertex{vert, color, normal});
            }
        }
        if (face == EnumFace::TOP) {
            for(auto& vert: TOP) {
                glm::vec4 normal = glm::vec4(0.0, 1.0, 0.0, 0.0);
                verts.push_back(Vertex{vert, color, normal});
            }
        }
        if (face == EnumFace::BOTTOM) {
            for(auto& vert: BOTTOM) {
                glm::vec4 normal = glm::vec4(0.0, -1.0, 0.0, 0.0);
                verts.push_back(Vertex{vert, color, normal});
            }
        }


        return verts;
    }

}



MiniCraft::MiniCraft() {
    this->m_Window = CreateRef<Window>(1080, 720, "MiniCraft");

    this->m_Camera = CreateRef<Camera>(45.0f, 0.1f, 100.0f);
    m_Camera->OnResize(m_Window->GetWidth(), m_Window->GetHeight());
    m_Camera->RecalculateView();


    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec4 aPos;
        layout (location = 1) in vec4 aColor;
        layout (location = 2) in vec4 aNormal;

        out vec4 fColor;
        out vec4 fNormal;

        uniform mat4 u_View;
        uniform mat4 u_Projection;
        uniform mat4 u_Model;
        void main() {
            fColor = aColor;
            fNormal = aNormal;
            gl_Position = u_Projection * u_View * u_Model * aPos;
        }
    )";

    std::string fragmentShaderSource = R"(
        #version 330 core
        in vec4 fColor;
        in vec4 fNormal;
        out vec4 FragColor;
        void main() {
            //color using normal
            FragColor = fColor;
        }
    )";

    this->m_Shader = CreateRef<ShaderProgram>(vertexShaderSource, fragmentShaderSource);


}


void MiniCraft::Init() {
    m_Window->Create();
    m_Shader->Create();

    glfwSetKeyCallback(m_Window->GetHandle(), [](GLFWwindow *, int key, int scancode, int action, int) {
        if(action == GLFW_PRESS && key == GLFW_KEY_F2) {
            MiniCraft::Get()->m_Wireframe = !MiniCraft::Get()->m_Wireframe;

            glPolygonMode(GL_FRONT_AND_BACK, MiniCraft::Get()->m_Wireframe ? GL_LINE : GL_FILL);

        }
    });


    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    auto frontVerts = faces::GetVerts(EnumFace::FRONT, glm::vec4(1.0, 0.0, 0.0, 1.0));
    auto backVerts = faces::GetVerts(EnumFace::BACK, glm::vec4(0.0, 1.0, 0.0, 1.0));
    auto leftVerts = faces::GetVerts(EnumFace::LEFT, glm::vec4(0.0, 0.0, 1.0, 1.0));
    auto rightVerts = faces::GetVerts(EnumFace::RIGHT, glm::vec4(1.0, 1.0, 0.0, 1.0));
    auto topVerts = faces::GetVerts(EnumFace::TOP, glm::vec4(0.0, 1.0, 1.0, 1.0));
    auto bottomVerts = faces::GetVerts(EnumFace::BOTTOM, glm::vec4(1.0, 0.0, 1.0, 1.0));


    std::vector<Vertex> verts;
    verts.insert(verts.end(), frontVerts.begin(), frontVerts.end());
    verts.insert(verts.end(), backVerts.begin(), backVerts.end());
    verts.insert(verts.end(), leftVerts.begin(), leftVerts.end());
    verts.insert(verts.end(), rightVerts.begin(), rightVerts.end());
    verts.insert(verts.end(), topVerts.begin(), topVerts.end());
    verts.insert(verts.end(), bottomVerts.begin(), bottomVerts.end());



    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(Vertex), verts.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(2);



    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void MiniCraft::Run() {
    double lastTime = glfwGetTime();
    while (!m_Window->ShouldClose()) {
        m_Window->Update();

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;
        OnUpdate(deltaTime);
        lastTime = currentTime;
    }
}

float sine(double x, float from, float to) {
    return from + (to - from) * (sin(x) + 1.0f) / 2.0f;
}

void MiniCraft::OnUpdate(double deltaTime) {

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    m_Camera->OnResize(m_Window->GetWidth(), m_Window->GetHeight());
    m_Camera->OnUpdate(deltaTime);


    glm::mat4 view = m_Camera->GetView();
    glm::mat4 projection = m_Camera->GetProjection();

    m_Shader->Bind();
    m_Shader->SetUniform("u_View", view);
    m_Shader->SetUniform("u_Projection", projection);
    glBindVertexArray(m_VAO);


    int size = 10;
    for(int x = -size/2; x < size/2; x++) {
            for(int z = -size/2; z < size/2; z++) {
                for(int y = 0; y < size; y++) {
                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(x, y, z));
                    m_Shader->SetUniform("u_Model", model);
                    glDrawArrays(GL_TRIANGLES, 0, 36);
                }

            }
    }




}

std::shared_ptr<MiniCraft> MiniCraft::m_Instance = nullptr;

