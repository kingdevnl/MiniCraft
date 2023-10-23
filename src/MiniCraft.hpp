#include "engine/Types.hpp"

class Window;
class ShaderProgram;

class MiniCraft {

public:
    MiniCraft();

    void Init();
    void Run();

    inline Ref<Window> GetWindow() const { return m_Window; }

private:
    Ref<Window> m_Window;
    Ref<ShaderProgram> m_Shader;


public:
    static std::shared_ptr<MiniCraft> m_Instance;
};
