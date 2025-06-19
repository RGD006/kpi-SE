#include "Events.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <nfd.h>

u32 color_red = 0xFF0000FF;
u32 color_yellow = 0xFFFF00FF;
u32 color_blue = 0x0000FFFF;
u32 color_green = 0x00FF00FF;
u32 color_pink = 0xFF66FFFF;
u32 color_purple = 0x990099FF;
u32 color_white = 0xFFFFFFFF;
u32 color_grey = 0x606060FF;
u32 color_black = 0x000000FF;
u32 color_eraser = 0x0;

SDL_Rect color_button_dest_red = {
    .x = 0,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_yellow = {
    .x = 50,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_blue = {
    .x = 100,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_green = {
    .x = 150,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_pink = {
    .x = 200,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_purple = {
    .x = 250,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_white = {
    .x = 300,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_grey = {
    .x = 350,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_black = {
    .x = 400,
    .y = 0,
    .w = 50,
    .h = 50,
};

SDL_Rect color_button_dest_eraser = {
    .x = 100,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_increase_pen_size = {
    .x = 0,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_decrease_pen_size = {
    .x = 50,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_change_pen_rect = {
    .x = 150,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_change_pen_circ = {
    .x = 200,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_set_rectangle_shape = {
    .x = 250,
    .y = 50,
    .w = 50,
    .h = 50,
};

SDL_Rect rect_set_circle_shape = {
    .x = 300,
    .y = 50,
    .w = 50,
    .h = 50,
};

void canvasUndo(void *arg)
{
    Canvas *canvas = reinterpret_cast<Canvas *>(arg);
    canvas->undo();
}

void canvasRedo(void *arg)
{
    Canvas *canvas = reinterpret_cast<Canvas *>(arg);
    canvas->redo();
}

void saveFile(void *arg)
{
    Canvas *canvas = reinterpret_cast<Canvas *>(arg);
    SDL_Texture *texture = canvas->getCanvasTexture();

    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_SaveDialog("bmp", nullptr, &outPath);
    if (result != NFD_OKAY)
    {
        if (result == NFD_CANCEL)
        {
            SDL_Log("User canceled save dialog.");
        }
        else
        {
            SDL_Log("Error: %s", NFD_GetError());
        }
        return;
    }

    SDL_Renderer *renderer = canvas->getRenderer();
    int width, height;
    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);

    SDL_Texture *target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_TARGET, width, height);

    SDL_SetRenderTarget(renderer, target);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);

    SDL_Surface *surface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_ARGB8888);
    SDL_RenderReadPixels(renderer, nullptr, SDL_PIXELFORMAT_ARGB8888, surface->pixels, surface->pitch);

    if (SDL_SaveBMP(surface, outPath) != 0)
    {
        SDL_Log("Failed to save file: %s", SDL_GetError());
    }

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(target);
    free(outPath);
}

void openFile(void *arg)
{
    Canvas *canvas = reinterpret_cast<Canvas *>(arg);

    nfdchar_t *outPath = nullptr;
    nfdresult_t result = NFD_OpenDialog("png", nullptr, &outPath);
    if (result != NFD_OKAY)
    {
        if (result == NFD_CANCEL)
        {
            SDL_Log("User canceled open dialog.");
        }
        else
        {
            SDL_Log("Open error: %s", NFD_GetError());
        }
        return;
    }

    SDL_Renderer *renderer = canvas->getRenderer(); // передбачаємо, що Canvas має getRenderer()
    SDL_Texture *background = IMG_LoadTexture(renderer, outPath);

    if (!background)
    {
        SDL_Log("Failed to load PNG: %s", IMG_GetError());
        free(outPath);
        return;
    }

    // Встановлюємо текстуру як фон canvas-а
    canvas->setBackgroundTexture(background);

    free(outPath);
}