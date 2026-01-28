#include <iostream>
#include <SDL3/SDL.h>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_render.h>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500

int main()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
	{
		std::cout << "SDL_VIDEO could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
	}
	
    std::cout << "SDL version is " << SDL_GetVersion() << std::endl;

    Uint32 flags = SDL_WINDOW_RESIZABLE;
    SDL_Window* m_window = SDL_CreateWindow("Chess", WINDOW_WIDTH, WINDOW_HEIGHT, flags);

    if(m_window == NULL)
    {
        std::cout << "Window could not be created! SDL_Error: "<< SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* m_renderer = SDL_CreateRenderer(m_window, nullptr);
    if (m_renderer == nullptr)
    {
        std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return 1;
    }

    SDL_FRect rect;
    rect.w = 100;
    rect.h = 100;
    rect.x = (WINDOW_WIDTH - rect.w) / 2.0f;
    rect.y = (WINDOW_HEIGHT - rect.h) / 2.0f;

    bool running = true;
    SDL_Event event;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else if (event.type == SDL_EVENT_KEY_DOWN)
            {
                if (event.key.key == SDLK_ESCAPE)
                    running = false;
            }
        }

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);

        SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
        if(!SDL_RenderRect(m_renderer, &rect))
        {
            std::cout << "Failed to draw rect: " << SDL_GetError() << std::endl;
        }
        SDL_RenderFillRect(m_renderer, &rect);

        SDL_RenderPresent(m_renderer);
    }

    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();

    return 0;
}