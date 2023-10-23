#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello, World!" << std::endl;

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
