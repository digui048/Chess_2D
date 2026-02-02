#include "Renderer.h"

#include "Core/Assert.h"
#include "Core/Log.h"
#include "Core/Window.h"
#include "Core/Application.h"

Renderer::Renderer()
{
    SDL_Window *window = Application::GetInstance().GetWindow()->GetSDLWindow();
    m_renderer = SDL_CreateRenderer(window, NULL);

    ASSERT(m_renderer == NULL, "SDL renderer is NULL!");

    background.r = 0;
    background.g = 0;
    background.b = 0;
    background.a = 255;
}

Renderer::~Renderer()
{
    if (m_renderer != nullptr)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = nullptr;
    }
}

void Renderer::RenderClear()
{
    SDL_RenderClear(m_renderer);
}

void Renderer::SwapWindow()
{
    SDL_SetRenderDrawColor(m_renderer, background.r, background.g, background.g, background.a);
    SDL_RenderPresent(m_renderer);
}

bool Renderer::DrawRectangle(const SDL_FRect &rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool filled)
{
    bool ret = true;
    float scale = (float)Application::GetInstance().GetWindowScale();

    SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(m_renderer, r, g, b, a);

    SDL_FRect rec(rect);
    rec.x *= scale;
    rec.y *= scale;
    rec.w *= scale;
    rec.h *= scale;

    bool result = (filled) ? SDL_RenderFillRect(m_renderer, &rec) : SDL_RenderRect(m_renderer, &rec);

    if (!result)
    {
        Log::Warn("Cannot draw quad to screen. SDL_RenderFillRect error: {}", SDL_GetError());
        ret = false;
    }

    return ret;
}

bool Renderer::DrawTexture(SDL_Texture *tex, const SDL_FRect* srcRect, const SDL_FRect *sect)
{
    bool ret = true;
    float scale = (float)Application::GetInstance().GetWindowScale();

    SDL_FRect scaleDst;
    if (sect)
    {
        scaleDst.x = sect->x * scale;
        scaleDst.y = sect->y * scale;
        scaleDst.w = sect->w * scale;
        scaleDst.h = sect->h * scale;
    }

    if (!SDL_RenderTexture(m_renderer, tex, srcRect, sect ? &scaleDst : nullptr))
    {
        Log::Warn("Cannot draw texture to screen, SDL_Error: {}", SDL_GetError());
        ret = false;
    }

    return ret;
}
