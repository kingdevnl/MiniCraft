#include <unordered_map>
#include <glm/glm.hpp>
#include "engine/Types.hpp"
#include "game/Chunk.hpp"

#pragma warning(disable: 4576)
#include "quickjspp.hpp"
#include "quickjs-libc.h"

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
    inline Ref<qjs::Context> GetJSContext() const { return m_JSContext; }
    inline Ref<qjs::Runtime> GetJSRuntime() const { return m_JSRuntime; }


private:
    Ref<Window> m_Window;
    Ref<Camera> m_Camera;
    Ref<ShaderProgram> m_Shader;
    Ref<TextureArray> m_TextureArray;
    Ref<BlockRegistry> m_BlockRegistry;

    std::unordered_map<glm::vec3, Chunk> m_Chunks;

    bool m_Wireframe = false;
    Ref<qjs::Runtime> m_JSRuntime;
    Ref<qjs::Context> m_JSContext;


public:
    inline static Ref<MiniCraft> Get() { return m_Instance; }
    static std::shared_ptr<MiniCraft> m_Instance;
};
