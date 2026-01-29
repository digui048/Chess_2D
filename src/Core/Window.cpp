#include "Window.h"
#include "Core/Log.h"
#include "Core/Assert.h"

Window::Window()
{
    ASSERT(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS), "SDL_VIDEO could not initialize! SDL_Error: {0}", SDL_GetError());

    m_window = SDL_CreateWindow("Chess", WINDOW_PREV_WIDTH, WINDOW_PREV_HEIGHT, SDL_WINDOW_RESIZABLE);

    ASSERT(m_window == NULL, "SDL window is NULL!");
}

Window::~Window()
{
    if (m_window != nullptr)
    {
        SDL_DestroyWindow(m_window);
        m_window = nullptr;
    }
}
