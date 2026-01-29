#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#define WINDOW_PREV_WIDTH 500
#define WINDOW_PREV_HEIGHT 500

class Window
{
public:
    Window();
    ~Window();

    SDL_Window* GetSDLWindow() const { return m_window; }

private:
    SDL_Window *m_window = nullptr;
};