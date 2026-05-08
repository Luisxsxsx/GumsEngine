#define SDL_MAIN_USE_CALLBACKS 1 // Usa uma chamada de funcao ao inves da main() original //
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGTH 720
#define NUM_POINTS 100

#include <iostream>
#include "math/Vector2d.cpp"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <vector>

/* Delcarando de forma statica ambos janela e renderizador */
static SDL_Window *main_window = nullptr;
static SDL_Renderer *main_render = nullptr;

// static SDL_FPoint points[NUM_POINTS];
static std::vector<GumsEngine::Vector2> points;
static std::vector<SDL_FPoint> pointsSDL;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) // AppInit é uma funcao de inicializacao onde declaramos e inicializamos tudo que envolve o inicio do programa
{
    SDL_SetAppMetadata("GumsEngine", "0.0.1", "com.gumsengine.main");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize video with SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("GumsEngine 0.0.1", WINDOW_WIDTH, WINDOW_HEIGTH, SDL_WINDOW_RESIZABLE, &main_window, &main_render))
    {
        SDL_Log("Couldn't create a window or renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Setando uma lógica de apresentacao da renderizacao desejada (*render, largura, altura, [logica] -> estrutura enumerada disponivel pelo SDL)
    SDL_SetRenderLogicalPresentation(main_render, WINDOW_WIDTH, WINDOW_HEIGTH, SDL_LOGICAL_PRESENTATION_LETTERBOX);

    int i;
    for (i = 0; i < NUM_POINTS; i++)
    {
        points.push_back(GumsEngine::Vector2{(SDL_randf() * ((float)WINDOW_WIDTH)),       // x
                                             SDL_randf() * ((float)WINDOW_HEIGTH)}); // y
        // std::cout << points.at(i);
    }
    pointsSDL.reserve(points.size());

    for (const auto &point : points)
    {
        pointsSDL.push_back(point.toSDLFPoint()); /* Convertendo para SDL_FPoint */
    }

    return SDL_APP_CONTINUE; /* CONTINUE COM O PROGRAMA! */
}

// controle de eventos //
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT)
        return SDL_APP_SUCCESS; /* finaliza o programa */

    return SDL_APP_CONTINUE; /* Continue o programa */
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_SetRenderDrawColor(main_render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(main_render);
    SDL_SetRenderDrawColor(main_render, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderPoints(main_render, pointsSDL.data(), SDL_arraysize(points));

    SDL_RenderPresent(main_render);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /*SDL limpa a janela e o render pra gente */
}