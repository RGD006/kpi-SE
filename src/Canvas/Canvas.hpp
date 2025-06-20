#pragma once
#include <SDL2/SDL_render.h>
#include <list>

#include "Object.hpp"
#include "Entity.hpp"

class Canvas : public Entity
{
private:
    SDL_Rect aim_destination;
    SDL_Texture *background_texture;
    SDL_Texture *canvas_texture;
    SDL_Texture *aim_texture;
    std::list<SDL_Texture *> prev_canvas_texture;
    std::list<SDL_Texture *> undo_canvas_texture;

public:
    Canvas(SDL_Renderer *, SDL_Point, int, int);
    Canvas();
    void render();
    SDL_Texture *getCanvasTexture();
    void undo(void);
    void redo(void);
    void saveCanvasRedo(SDL_Texture *texture);
    void saveCanvasUndo(SDL_Texture *texture);
    void setBackground(color_t, SDL_Rect *);
    void setBackgroundTexture(SDL_Texture *texture);
    void setCanvasTexture(SDL_Texture *texture);
    void setScale(SDL_Rect new_scale);
    void setAimTexture(Object *);
    void addObject(Object *);
    void fillAt(i32 x, i32 y, color_t fill_color);
};
