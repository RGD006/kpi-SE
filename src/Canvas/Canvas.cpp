#include "Canvas.hpp"
#include <queue>
#include <iostream>

#define MAX_QUEUE_SIZE (15)

Canvas::Canvas()
    : Entity(createRect(0, 0, 0, 0), nullptr)
{
}

Canvas::Canvas(SDL_Renderer *window_renderer, SDL_Point start_point, int _w, int _h)
    : Entity(createRect(start_point.x, start_point.y, _w, _h), window_renderer)
{
    renderer = window_renderer;
    if (!renderer)
    {
        std::cerr << "Error with init renderer: " << SDL_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    canvas_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _w, _h);
    background_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, _w, _h);
    aim_texture = nullptr;

    SDL_SetTextureBlendMode(canvas_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureBlendMode(background_texture, SDL_BLENDMODE_BLEND);
}

// set in one color background_texture
void Canvas::setBackground(color_t color, SDL_Rect *rect)
{
    // resize background size for canvas size
    if (rect->w != destination_rect.w || rect->h != destination_rect.h)
    {
        rect->w = destination_rect.w;
        rect->h = destination_rect.h;
    }

    SDL_SetRenderTarget(renderer, background_texture);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    if (rect)
        SDL_RenderFillRect(renderer, rect);
    else
        SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::addObject(Object *object)
{
    SDL_SetRenderTarget(renderer, canvas_texture);
    object->render(renderer);
    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::saveCanvasRedo(SDL_Texture *texture)
{
    SDL_Texture *new_prev_texture = Entity::copyTexture(renderer, texture, destination_rect.w, destination_rect.h);

    if (prev_canvas_texture.size() <= MAX_QUEUE_SIZE)
    {
        prev_canvas_texture.push_front(new_prev_texture);
    }
    else
    {
        SDL_Texture *delete_prev_texture = prev_canvas_texture.front();
        prev_canvas_texture.pop_back();
        SDL_DestroyTexture(delete_prev_texture);
        prev_canvas_texture.push_front(new_prev_texture);
    }
}

void Canvas::saveCanvasUndo(SDL_Texture *texture)
{
    SDL_Texture *new_prev_texture = Entity::copyTexture(renderer, texture, destination_rect.w, destination_rect.h);

    if (undo_canvas_texture.size() <= MAX_QUEUE_SIZE)
    {
        undo_canvas_texture.push_front(new_prev_texture);
    }
    else
    {
        SDL_Texture *delete_undo_texture = prev_canvas_texture.front();
        undo_canvas_texture.pop_back();
        SDL_DestroyTexture(delete_undo_texture);
        undo_canvas_texture.push_front(new_prev_texture);
    }
}

void Canvas::render()
{
    SDL_RenderCopy(renderer, background_texture, nullptr, &destination_rect); // draw background_texture
    SDL_RenderCopy(renderer, canvas_texture, nullptr, &destination_rect);     // draw canvas

    if (aim_texture)
    {
        SDL_RenderCopy(renderer, aim_texture, nullptr, &aim_destination);
    }

    SDL_SetRenderTarget(renderer, nullptr);
}

void Canvas::setAimTexture(Object *aim)
{
    if (aim)
    {
        aim_destination = {
            .x = aim->getStartPoints()->x,
            .y = aim->getStartPoints()->y,
            .w = aim->getW(),
            .h = aim->getH(),
        };

        if (!aim_texture)
        {
            aim_texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, aim_destination.w, aim_destination.h);
            SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        }
        else
        {
            SDL_SetRenderTarget(renderer, aim_texture);
            SDL_RenderClear(renderer);
            aim->render(renderer);
            SDL_SetRenderTarget(renderer, nullptr);
        }
    }
    else
    {
        SDL_SetRenderTarget(renderer, aim_texture);
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderFillRect(renderer, &aim_destination);
        SDL_SetRenderTarget(renderer, nullptr);
        SDL_DestroyTexture(aim_texture);
        aim_texture = nullptr;
    }
}

SDL_Texture *Canvas::getCanvasTexture()
{
    return canvas_texture;
}

void Canvas::undo(void)
{
    if (!undo_canvas_texture.empty())
    {
        SDL_Texture *prev = undo_canvas_texture.front();
        undo_canvas_texture.pop_front();

        canvas_texture = Entity::copyTexture(renderer, prev, destination_rect.w, destination_rect.h);

        saveCanvasRedo(canvas_texture);

        SDL_DestroyTexture(prev);
    }
}

void Canvas::redo(void)
{
    if (!prev_canvas_texture.empty())
    {
        SDL_Texture *redo_tex = prev_canvas_texture.front();
        prev_canvas_texture.pop_front();

        canvas_texture = Entity::copyTexture(renderer, redo_tex, destination_rect.w, destination_rect.h);

        saveCanvasUndo(canvas_texture);

        SDL_DestroyTexture(redo_tex);
    }
}

void Canvas::fillAt(i32 x, i32 y, color_t fill_color)
{
    int width = destination_rect.w;
    int height = destination_rect.h;

    // Выделяем буфер под пиксели
    std::vector<u32> pixels(width * height);
    SDL_Rect rect = {0, 0, width, height};

    // Считываем пиксели напрямую из canvas_texture
    if (SDL_SetRenderTarget(renderer, canvas_texture) != 0 ||
        SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_RGBA8888, pixels.data(), width * sizeof(u32)) != 0)
    {
        std::cerr << "Failed to read pixels: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetRenderTarget(renderer, nullptr);

    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
    u32 start_color = pixels[y * width + x];

    u8 sr, sg, sb;
    SDL_GetRGB(start_color, format, &sr, &sg, &sb);

    if (fill_color.r == sr && fill_color.g == sg && fill_color.b == sb)
    {
        SDL_FreeFormat(format);
        return;
    }

    u32 new_color = SDL_MapRGBA(format, fill_color.r, fill_color.g, fill_color.b, fill_color.a);

    std::queue<std::pair<int, int>> q;
    q.push({x, y});

    while (!q.empty())
    {
        auto [cx, cy] = q.front();
        q.pop();

        if (cx < 0 || cy < 0 || cx >= width || cy >= height)
            continue;

        u32 &current_pixel = pixels[cy * width + cx];
        u8 r, g, b;
        SDL_GetRGB(current_pixel, format, &r, &g, &b);

        if (r != sr || g != sg || b != sb)
            continue;

        current_pixel = new_color;

        q.push({cx + 1, cy});
        q.push({cx - 1, cy});
        q.push({cx, cy + 1});
        q.push({cx, cy - 1});
    }

    SDL_FreeFormat(format);

    SDL_Texture *result = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_STREAMING, width, height);
    SDL_UpdateTexture(result, nullptr, pixels.data(), width * sizeof(u32));
    SDL_SetTextureBlendMode(result, SDL_BLENDMODE_BLEND);

    SDL_SetRenderTarget(renderer, canvas_texture);
    SDL_RenderCopy(renderer, result, nullptr, nullptr);
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_DestroyTexture(result);
}

void Canvas::setBackgroundTexture(SDL_Texture *texture)
{
    background_texture = texture;
}

void Canvas::setCanvasTexture(SDL_Texture *texture)
{
    canvas_texture = texture;
}

void Canvas::setScale(SDL_Rect new_scale)
{
    destination_rect = new_scale;
}