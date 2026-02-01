#pragma once

#include "Utils/Vector2D.h"
#include "SDL3/SDL.h"

class Renderer
{
public:
    Renderer();
    ~Renderer();

    void RenderClear();
    void SwapWindow();

    bool DrawRectangle(const SDL_FRect &rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled = true);
    bool DrawTexture(SDL_Texture *tex, const SDL_FRect* srcRect = NULL, const SDL_FRect *sect = NULL);

    SDL_Renderer *GetRenderer() const { return m_renderer; }

private:
    SDL_Renderer *m_renderer;
    SDL_Color background;
};