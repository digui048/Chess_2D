#include "Core/Application.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    /*SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
    if(!SDL_RenderRect(m_renderer, &rect))
    {
        std::cout << "Failed to draw rect: " << SDL_GetError() << std::endl;
    }
    SDL_RenderFillRect(m_renderer, &rect);

    SDL_RenderPresent(m_renderer);
    */

    Application* app = new Application();
    app->Run();
    delete app;
}