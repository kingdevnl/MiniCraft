#pragma once
#include <string>

struct GLFWwindow;

class Window {

public:
    Window(int width, int height, const char* title);

    void Create();

    void Update();
    bool ShouldClose() const;

    void SetTitle(std::string title);

    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline GLFWwindow* GetHandle() const { return m_Handle; }




private:
    int m_Width, m_Height;
    const char* m_Title;
    GLFWwindow* m_Handle;


};