#include "engine/Types.hpp"

class Window;
class ShaderProgram;
class Camera;

class MiniCraft {

public:
    MiniCraft();

    void Init();
    void Run();
    void OnUpdate(double deltaTime);

    inline Ref<Window> GetWindow() const { return m_Window; }
    inline Ref<Camera> GetCamera() const { return m_Camera; }


private:
    Ref<Window> m_Window;
    Ref<Camera> m_Camera;
    Ref<ShaderProgram> m_Shader;
    uint m_VAO, m_VBO;

    bool m_Wireframe = false;


public:
    inline static Ref<MiniCraft> Get() { return m_Instance; }
    static std::shared_ptr<MiniCraft> m_Instance;
};
