#include <spdlog/spdlog.h>
#include <GLFW/glfw3.h>

int main() {
    spdlog::info("Hello, World!");
    glfwInit();
    glfwDefaultWindowHints();
    auto window = glfwCreateWindow(640, 480, "Hello, World!", nullptr, nullptr);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
