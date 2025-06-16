#include "Button.hpp"
#include "Object.hpp"
#include <SDL2/SDL_image.h>
#include <fstream>

Button::Button(i32 button_event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render)
{
    if (!_window_render)
        throw "window renderer is nullptr";

    texture = nullptr;
    event.type = SDL_USEREVENT;
    event.user.code = button_event;
    renderer = _window_render;
    s_rect = _size;
    d_rect = _dest;
}

Button::Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, SDL_Texture *texture)
    : Button(event, _size, _dest, _window_render)
{
    setTexture(texture);
}

Button::Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, const char *path_to_texture)
    : Button(event, _size, _dest, _window_render)
{
    setTexture(path_to_texture);
}

Button::Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, u32 color)
    : Button(event, _size, _dest, _window_render)
{
    setTexture(color);
}

void Button::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

void Button::setTexture(u32 color)
{
    SDL_Rect rect = {0, 0, d_rect.w, d_rect.h};
    texture = SDL_CreateTexture(renderer,
                                SDL_PIXELFORMAT_RGBA8888,
                                SDL_TEXTUREACCESS_TARGET,
                                50, 50);
    color_t rect_color(color);
    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, rect_color.r, rect_color.g, rect_color.b, rect_color.a);
    SDL_RenderClear(renderer);
    SDL_RenderFillRect(renderer, &rect);
}

void Button::setTexture(const char *path)
{
    if (texture)
        SDL_DestroyTexture(texture);

    texture = IMG_LoadTexture(renderer, path);

    if (!texture)
        throw "No texture";
}

#include <iostream>

void Button::render()
{
    if (!texture)
        throw "No texture";

    if (isEmptyRect(s_rect))
    {
        SDL_RenderCopy(renderer, texture, nullptr, &d_rect);
    }
    else
    {
        SDL_RenderCopy(renderer, texture, &s_rect, &d_rect);
    }
}

void Button::listenMouse(Mouse &mouse)
{
    SDL_Rect *mouse_release = reinterpret_cast<SDL_Rect *>(mouse.releaseLeft(nullptr));

    if (mouse_release)
    {
        if (SDL_HasIntersection(&d_rect, mouse_release) == SDL_TRUE)
        {
            std::cout << "Button is selected!" << std::endl;
            SDL_PushEvent(&event);
        }
    }
}

Button::~Button()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}