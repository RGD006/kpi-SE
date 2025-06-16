#include <Window.hpp>
#include "Shapes.hpp"
#include "Pen.hpp"
#include <iostream>

void exitWindow(void *arg)
{
    *((bool *)arg) = false;
    std::cout << "Exit event" << std::endl;
}

Window::Window(const char *window_title, u32 w, u32 h)
    : width(w), height(h)
{
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    canvas = Canvas(window, createPoint(0, 200), 800, 800);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow error:" << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }
}

void Window::run(void)
{
    bool window_run = true;

    SDL_Rect canvas_background = {
        .x = 0,
        .y = 0,
        .w = 800,
        .h = 800,
    };
    color_t color_canvas_background(0xFFFFFFFF);

    canvas.setBackground(color_canvas_background, &canvas_background);
    
    Rectangle *rect = new Rectangle(10, 10, createPoint(0, 0));
    rect->setColor(color_t(0xFF0000FF));

    event_handler.addEvent(SDL_QUIT, exitWindow, reinterpret_cast<void *>(&window_run));

    Pen pen(rect);
    pen.addCanvas(&canvas);

    auto pen_mouse_down_evnt = [&pen](void *arg)
    { pen.eventMouseDown(arg); };
    auto pen_mouse_move_evnt = [&pen](void *arg)
    { pen.eventMouseMove(arg); };
    auto pen_mouse_up_evnt = [&pen](void *arg)
    { pen.eventMouseUp(arg); };

    event_handler.addButtonEvent(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT, pen_mouse_down_evnt, pen.getMoveState());
    event_handler.addButtonEvent(SDL_MOUSEMOTION, SDL_NO_BUTTON, pen_mouse_move_evnt, pen.getMoveState());
    event_handler.addButtonEvent(SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT, pen_mouse_up_evnt, pen.getMoveState());

    while (window_run)
    {
        event_handler.run();
        canvas.render();
    }

}