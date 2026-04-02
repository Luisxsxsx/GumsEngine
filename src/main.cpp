#include <iostream>
#include <SDL3/SDL.h>

int checkRGBIncrease(int rgb)
{
    const int max_limit = 255;
    const int min_limit = 0;

    if (rgb >= max_limit)
        return -1; // decrease

    if (rgb <= min_limit)
        return 1; // increase

    return 0; // Does nothing
}

int main(int argc, char *argv[])
{
    // std::cout << "Hello World" << std::endl;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
                  << std::endl;

        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow(
        "GumsEngine ver. 0.0.1",
        800,
        600,
        SDL_WINDOW_RESIZABLE);

    if (window == nullptr)
    {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
                  << std::endl;

        SDL_DestroyWindow(window);

        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, NULL);

    if (!renderer)
    {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
                  << std::endl;

        SDL_DestroyWindow(window);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Event event;
    bool running = true,
         increaseR = true,
         increaseG = true,
         increaseB = true;
    int r = 242,
        g = 72,
        b = 5;
    while (running)
    {
        if (checkRGBIncrease(r) == -1)
            increaseR = false;
        else if (checkRGBIncrease(r) == 1)
            increaseR = true;

        if (checkRGBIncrease(g) == -1)
            increaseG = false;
        else if (checkRGBIncrease(g) == 1)
            increaseG = true;

        if (checkRGBIncrease(b) == -1)
            increaseB = false;
        else if (checkRGBIncrease(b) == 1)
            increaseB = true;

        if (increaseR)
            r++;
        else
            r--;

        if (increaseG)
            g++;
        else
            g--;

        if (increaseB)
            b++;
        else
            b--;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_EVENT_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_UpdateWindowSurface(window);

        SDL_Delay(16);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}