#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Window.hpp"

Window::Window(int width, int height, const char *title)
        : m_Width(width), m_Height(height), m_Title(title) {

}


void Window::Create() {

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW!");
    }

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    this->m_Handle = glfwCreateWindow(m_Width, m_Height, m_Title, nullptr, nullptr);

    //center the window
    const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(m_Handle, (mode->width - m_Width) / 2, (mode->height - m_Height) / 2);

    glfwShowWindow(m_Handle);
    glfwMakeContextCurrent(m_Handle);
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW!");
    }

    glfwSwapInterval(1);
}


void Window::Update() {
    glfwGetFramebufferSize(m_Handle, &m_Width, &m_Height);
    if (m_Width < 5) m_Width = 5;
    if (m_Height < 5) m_Height = 5;

    glfwSwapBuffers(m_Handle);
    glfwPollEvents();

    glViewport(0, 0, m_Width, m_Height);



}


bool Window::ShouldClose() const {
    return glfwWindowShouldClose(m_Handle);
}

void Window::SetTitle(std::string title) {
    const char *cstr = title.c_str();
    glfwSetWindowTitle(m_Handle, cstr);
}
