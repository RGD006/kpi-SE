#include "Button.hpp"
#include "Object.hpp"
#include <SDL2/SDL_image.h>
#include <fstream>
#include <iostream>

Button::Button(i32 button_event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render)
    : Entity(button_event, _size, _dest, _window_render)
{
}

Button::Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, SDL_Texture *texture)
    : Entity(event, _size, _dest, _window_render, texture)
{
}

Button::Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, const char *path_to_texture)
    : Entity(event, _size, _dest, _window_render, path_to_texture)
{
}

Button::Button(i32 event, SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, u32 color)
    : Entity(event, _size, _dest, _window_render, color)
{
}

void Button::render()
{
    if (!texture)
        throw "No texture";

    if (isEmptyRect(source_rect))
    {
        SDL_RenderCopy(renderer, texture, nullptr, &destination_rect);
    }
    else
    {
        SDL_RenderCopy(renderer, texture, &source_rect, &destination_rect);
    }
}

void Button::listenMouse(Mouse &mouse)
{
    if (mouse.getState(MOUSE_CLICK))
    {
        // std::cout << "Mouse pressed " << mouse.getTipPos()->x << " " << mouse.getTipPos()->y << std::endl;
        if (SDL_HasIntersection(&destination_rect, mouse.getTipPos()) == SDL_TRUE)
        {
            // std::cout << "Button is selected!" << std::endl;
            SDL_PushEvent(&event);
        }
    }
}

Button::~Button()
{

}