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
    Log::Info("Renderer creted successfully");
}

Application::~Application()
{
    Log::Info("Closing Application...");

    delete (m_renderer);
    m_renderer = nullptr;

    delete (m_window);
    m_window = nullptr;

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
    while (m_running)
    {
        m_inputManager.Update();
        ProcessEvents(m_inputManager);

        m_renderer->RenderClear();

        // update render HERE!!!!!!!!
        SDL_FRect rect = {0.0f, 0.0f, 100.0f, 100.0f};
        m_renderer->DrawRectangle(rect, 255, 0, 255, 255);

        m_renderer->SwapWindow();
    }
}

void Application::Close()
{
    m_running = false;
}
