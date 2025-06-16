#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

class Button
{
private:
    SDL_Rect s_rect, d_rect;
    SDL_Texture *texture;
    SDL_Renderer *renderer;
    bool is_selected;

public:
    Button(SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render);
    Button(SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, SDL_Texture *texture);
    Button(SDL_Rect _size, SDL_Rect _dest, SDL_Renderer *_window_render, const char *path_to_texture);
    void setTexture(SDL_Texture *texture);
    void setTexture(const char *path);
    void render(void);
    ~Button();
};
