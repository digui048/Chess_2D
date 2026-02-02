#pragma once

#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#include <string>

#define WINDOW_PREV_WIDTH 608
#define WINDOW_PREV_HEIGHT 576

class Window
{
public:
    Window();
    ~Window();

    SDL_Window *GetSDLWindow() const { return m_window; }
    void GetWindowSize(int &w, int &h);
    inline int GetScale() const { return scale; }

    void SetTitle(std::string name);

private:
    SDL_Window *m_window = nullptr;
    int scale = 1;
};