#include "Button.hpp"
#include "Object.hpp"
#include <SDL2/SDL_image.h>
#include <fstream>

Button::Button(SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render)
{
    if (!_window_render)
        throw "window renderer is nullptr";
    renderer = _window_render;
    s_rect = _size;
    d_rect = _dest;
}

Button::Button(SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, SDL_Texture *texture)
{
    *this = Button(_size, _dest, _window_render);
    setTexture(texture);
}

Button::Button(SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, const char *path_to_texture)
{
    *this = Button(_size, _dest, _window_render);
    setTexture(path_to_texture);
}

void Button::setTexture(SDL_Texture *texture)
{
    this->texture = texture;
}

void Button::setTexture(const char *path)
{
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, s_rect.w, s_rect.h);
    texture = IMG_LoadTexture(renderer, path);
}

#include <iostream>

void Button::render()
{
    // if (isEmptyRect(d_rect))
    // {
    // std::cout << "empty dest" << std::endl;
    SDL_RenderCopy(renderer, texture, nullptr, &d_rect);
    // }
}

Button::~Button()
{
    if (texture)
    {
        SDL_DestroyTexture(texture);
    }
}