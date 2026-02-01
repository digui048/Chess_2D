#include "Application.h"
#include "TextureImporter.h"

#include "Core/Assert.h"
#include "Core/Log.h"

Application *Application::s_Instance = nullptr;

Application::Application()
{
    Log::Init();
    Log::Info("Starting Application...");

    ASSERT(s_Instance != nullptr, "Application is already created");
    s_Instance = this;

    Log::Info("Application Started");

    m_window = new Window();
    Log::Info("Window created successfully");

    m_renderer = new Renderer();
    Log::Info("Renderer created successfully");

    m_scene = new Scene();
    Log::Info("Scene created successfully");
}

Application::~Application()
{
    Log::Info("Closing Application...");

    delete (m_renderer);
    m_renderer = nullptr;

    delete (m_window);
    m_window = nullptr;

    delete (m_scene);
    m_scene = nullptr;

    SDL_Quit();

    Log::Info("Application Closed");
}

Application &Application::GetInstance()
{
    return *s_Instance;
}

void Application::ProcessEvents(InputEventManager &eventController)
{
    if (eventController.HasEvent(SDL_EVENT_QUIT))
    {
        Close();
        return;
    }

    if (eventController.HasEvent(SDL_EVENT_KEY_DOWN))
    {
        if (eventController.GetKeyStatus(SDL_SCANCODE_ESCAPE) == KeyState::DOWN)
        {
            Close();
        }
    }
}

void Application::Run()
{
    //SDL_Texture *tex = TextureImporter::Load("assets/Textures/defaultTexture.png");

    m_scene->CreateScene();
    Log::Info("Scene created");

    while (m_running)
    {
        m_inputManager.Update();
        ProcessEvents(m_inputManager);

        m_renderer->RenderClear();

        m_scene->Update();

        m_renderer->SwapWindow();
    }
}

void Application::Close()
{
    m_running = false;
}
