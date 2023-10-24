#include <unordered_map>
#include <glm/glm.hpp>
#include "engine/Types.hpp"
#include "game/Chunk.hpp"

class Window;
class ShaderProgram;
class Camera;
class TextureArray;
class BlockRegistry;

class MiniCraft {

public:
    MiniCraft();
    ~MiniCraft();

    void Init();
    void InitImGui();
    void Run();
    void OnUpdate(double deltaTime);

    inline Ref<Window> GetWindow() const { return m_Window; }
    inline Ref<Camera> GetCamera() const { return m_Camera; }
    inline Ref<TextureArray> GetTextureArray() const { return m_TextureArray; }
    inline Ref<BlockRegistry> GetBlockRegistry() const { return m_BlockRegistry; }

private:
    Ref<Window> m_Window;
    Ref<Camera> m_Camera;
    Ref<ShaderProgram> m_Shader;
    Ref<TextureArray> m_TextureArray;
    Ref<BlockRegistry> m_BlockRegistry;

    std::unordered_map<glm::vec3, Chunk> m_Chunks;

    uint m_VAO, m_VBO;

    bool m_Wireframe = false;


public:
    inline static Ref<MiniCraft> Get() { return m_Instance; }
    static std::shared_ptr<MiniCraft> m_Instance;
};
