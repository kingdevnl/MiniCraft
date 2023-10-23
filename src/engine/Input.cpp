#include "engine/Input.hpp"
#include "engine/Window.hpp"
#include "MiniCraft.hpp"
#include <GLFW/glfw3.h>

bool Input::IsKeyDown(KeyCode keycode) {
    GLFWwindow* windowHandle = MiniCraft::Get()->GetWindow()->GetHandle();

    int state = glfwGetKey(windowHandle, (int)keycode);
    return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool Input::IsMouseButtonDown(MouseButton button) {
    GLFWwindow* windowHandle = MiniCraft::Get()->GetWindow()->GetHandle();

    int state = glfwGetMouseButton(windowHandle, (int)button);
    return state == GLFW_PRESS;
}

glm::vec2 Input::GetMousePosition() {
    GLFWwindow* windowHandle = MiniCraft::Get()->GetWindow()->GetHandle();

    double x, y;
    glfwGetCursorPos(windowHandle, &x, &y);
    return { (float)x, (float)y };
}

void Input::SetCursorMode(CursorMode mode) {
    GLFWwindow* windowHandle = MiniCraft::Get()->GetWindow()->GetHandle();

    glfwSetInputMode(windowHandle, GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
}