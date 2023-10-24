#include <vector>
#include <spdlog/spdlog.h>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "MiniCraft.hpp"
#include "vendor/BS_thread_pool.hpp"
#include "engine/Window.hpp"
#include "engine/Camera.hpp"
#include "engine/ShaderProgram.hpp"
#include "engine/TextureArray.hpp"
#include "game/BlockRegistry.hpp"
#include "game/Chunk.hpp"
#include "engine/Timer.hpp"


BS::thread_pool pool(4);


MiniCraft::MiniCraft() {
    this->m_Window = CreateRef<Window>(1080, 720, "MiniCraft");

    this->m_Camera = CreateRef<Camera>(45.0f, 0.1f, 200.0f);
    m_Camera->OnResize(m_Window->GetWidth(), m_Window->GetHeight());
    m_Camera->RecalculateView();


    this->m_Shader = ShaderProgram::FromFile("assets/shaders/basic.vert.glsl", "assets/shaders/basic.frag.glsl");

    this->m_TextureArray = CreateRef<TextureArray>();
    this->m_BlockRegistry = CreateRef<BlockRegistry>(m_TextureArray);


}

MiniCraft::~MiniCraft() {
}


void MiniCraft::Init() {
    m_Window->Create();

    m_Shader->Create();
    m_TextureArray->Create();

    m_Camera->SetPosition({-0.91402066, 55.045845, 6.0809617});

    InitImGui();

    m_BlockRegistry->LoadFromFile("assets/blocks.json");

    glm::vec3 startPos = glm::vec3(0, 0, 0);
    int radius = 10;

    for (int x = -radius / 2; x < radius / 2; x++) {
        for (int z = -radius / 2; z < radius / 2; z++) {
            pool.submit([](int x, int z) {
                auto chunk = Chunk(glm::vec3(x, 0, z));
                chunk.Generate();
                chunk.BuildMesh();
                MiniCraft::Get()->m_Chunks.insert({chunk.GetChunkPos(), chunk});
            }, x, z);
        }
    }


    glfwSetKeyCallback(m_Window->GetHandle(), [](GLFWwindow *, int key, int scancode, int action, int) {
        if (action == GLFW_PRESS && key == GLFW_KEY_F2) {
            MiniCraft::Get()->m_Wireframe = !MiniCraft::Get()->m_Wireframe;
            glPolygonMode(GL_FRONT_AND_BACK, MiniCraft::Get()->m_Wireframe ? GL_LINE : GL_FILL);
        }
        if (action == GLFW_PRESS && key == GLFW_KEY_END) {
            auto camPos = MiniCraft::Get()->m_Camera->GetPosition();

            glm::vec3 chunkPos = glm::vec3(floor(camPos.x / CHUNK_SIZE), 0, floor(camPos.z / CHUNK_SIZE));
            Chunk chunk = Chunk(chunkPos);
            chunk.Generate();
            chunk.BuildMesh();
            MiniCraft::Get()->m_Chunks.insert({chunk.GetChunkPos(), chunk});
            spdlog::info("Camera Position: ({}, {}, {})", camPos.x, camPos.y, camPos.z);
        }
    });


}

void MiniCraft::InitImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_Window->GetHandle(), true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void MiniCraft::Run() {
    double lastTime = glfwGetTime();
    while (!m_Window->ShouldClose()) {
        m_Window->Update();

        double currentTime = glfwGetTime();
        double deltaTime = currentTime - lastTime;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        OnUpdate(deltaTime);
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        lastTime = currentTime;
    }
}

std::string VecToString(glm::vec3 vec) {
    return "(" + std::to_string(vec.x) + ", " + std::to_string(vec.y) + ", " + std::to_string(vec.z) + ")";
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
    m_Shader->SetUniform1i("texArray", m_TextureArray->GetTextureID());


    for (auto &[k, v]: m_Chunks) {
        v.Render(m_Shader);
    }



}

std::shared_ptr<MiniCraft> MiniCraft::m_Instance = nullptr;

