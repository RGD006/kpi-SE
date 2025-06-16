#include <Window.hpp>
#include "SDL2/SDL_image.h"
#include "Shapes.hpp"
#include "Pen.hpp"
#include "ButtonEvents.hpp"
#include <iostream>

void exitWindow(void *arg)
{
    *((bool *)arg) = false;
    // std::cout << "Exit event" << std::endl;
}

Window::Window(const char *window_title, u32 w, u32 h)
    : width(w), height(h)
{
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cerr << "IMG init error " << IMG_GetError() << std::endl; 
        exit(EXIT_FAILURE);
    }
        
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    canvas = Canvas(renderer, createPoint(0, 200), 800, 800);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow error:" << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }
}

void Window::run(void)
{
    bool window_run = true;

    SDL_Rect canvas_background = {0};
    color_t color_canvas_background(0xFFFFFFFF);

    canvas.setBackground(color_canvas_background, &canvas_background);

    Rectangle *rect = new Rectangle(10, 10, createPoint(0, 0));
    rect->setColor(color_t(0xFF0000FF));

    Pen pen(rect);
    pen.addCanvas(&canvas);
    
    auto pen_mouse_down_evnt = [&pen](void *arg)
    { pen.eventMouseDown(arg); };
    auto pen_mouse_move_evnt = [&pen](void *arg)
    { pen.eventMouseMove(arg); };
    auto pen_mouse_up_evnt = [&pen](void *arg)
    { pen.eventMouseUp(arg); };
    
    Button button_save = Button(BUTTON_SAVE, createRect(0, 0, 0, 0), createRect(0, 0, 100, 100), renderer, "images/cat.png");
    
    buttons.push_back(button_save);
    
    event_handler.addEvent(SDL_QUIT, exitWindow, reinterpret_cast<void *>(&window_run));
    event_handler.addIOEvent(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT, pen_mouse_down_evnt, pen.getMoveState());
    event_handler.addIOEvent(SDL_MOUSEMOTION, SDL_NO_BUTTON, pen_mouse_move_evnt, pen.getMoveState());
    event_handler.addIOEvent(SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT, pen_mouse_up_evnt, pen.getMoveState());
    event_handler.addButton(button_save);

    
    while (window_run)
    {
        SDL_SetRenderTarget(renderer, nullptr);
        
        event_handler.run();

        for (auto &button : buttons)
        {
            button.render();
        }
        
        canvas.render();
        SDL_RenderPresent(renderer);
    }
}