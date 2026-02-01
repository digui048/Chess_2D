#pragma once

#include "Core/Window.h"
#include "Core/Renderer.h"
#include "Core/InputEventManager.h"
#include "Scene/Scene.h"
#include <vector>

class Application
{
public:
    Application();
    ~Application();

    void Run();
    void Close();

    static Application &GetInstance();

    Window* GetWindow() const { return m_window; }
    InputEventManager& GetInputManager() { return m_inputManager; }
    Renderer* GetRenderer() const { return m_renderer; }

private:
    void ProcessEvents(InputEventManager &eventController);

private:
    static Application* s_Instance;

    Window *m_window = nullptr;
    Renderer *m_renderer = nullptr;
    InputEventManager m_inputManager;
    Scene* m_scene = nullptr;

    bool m_running = true;
};
