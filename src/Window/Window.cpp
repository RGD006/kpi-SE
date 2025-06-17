#include <Window.hpp>
#include "SDL2/SDL_image.h"
#include "Shapes.hpp"
#include "Pen.hpp"
#include "ButtonEvents.hpp"
#include <iostream>

void exitWindow(void *arg)
{
    *((bool *)arg) = false;
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
    SDL_Rect window_background = {
        .x = 0,
        .y = 0,
        .w = width,
        .h = height,
    };

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
    auto pen_change_color = [&pen](void *arg)
    {  pen.changeColor(*reinterpret_cast<u32 *>(arg)); };
    auto pen_increase_size = [&pen](void *arg)
    { pen.increaseSize(*reinterpret_cast<u32 *>(arg)); };
    auto pen_decrease_size = [&pen](void *arg)
    { pen.decreaseSize(*reinterpret_cast<u32 *>(arg)); };

    u32 change_pen_size = 20;

    Button button_red(BUTTON_CHANGE_COLOR_RED, createRect(0, 0, 0, 0), color_button_dest_red, renderer, color_red);
    Button button_yellow(BUTTON_CHANGE_COLOR_YELLOW, createRect(0, 0, 0, 0), color_button_dest_yellow, renderer, color_yellow);
    Button button_blue(BUTTON_CHANGE_COLOR_BLUE, createRect(0, 0, 0, 0), color_button_dest_blue, renderer, color_blue);
    Button button_green(BUTTON_CHANGE_COLOR_GREEN, createRect(0, 0, 0, 0), color_button_dest_green, renderer, color_green);
    Button button_pink(BUTTON_CHANGE_COLOR_PINK, createRect(0, 0, 0, 0), color_button_dest_pink, renderer, color_pink);
    Button button_purple(BUTTON_CHANGE_COLOR_PURPLE, createRect(0, 0, 0, 0), color_button_dest_purple, renderer, color_purple);
    Button button_white(BUTTON_CHANGE_COLOR_WHITE, createRect(0, 0, 0, 0), color_button_dest_white, renderer, color_white);
    Button button_grey(BUTTON_CHANGE_COLOR_GREY, createRect(0, 0, 0, 0), color_button_dest_grey, renderer, color_grey);
    Button button_black(BUTTON_CHANGE_COLOR_BLACK, createRect(0, 0, 0, 0), color_button_dest_black, renderer, color_black);
    Button button_increase_pen_size(BUTTON_INCREASE_PEN_SIZE, createRect(0, 0, 0, 0), rect_increase_pen_size, renderer, "images/plus.png");
    Button button_decrease_pen_size(BUTTON_DECREASE_PEN_SIZE, createRect(0, 0, 0, 0), rect_decrease_pen_size, renderer, "images/minus.png");

    buttons.push_back(&button_red);
    buttons.push_back(&button_yellow);
    buttons.push_back(&button_blue);
    buttons.push_back(&button_green);
    buttons.push_back(&button_pink);
    buttons.push_back(&button_purple);
    buttons.push_back(&button_white);
    buttons.push_back(&button_grey);
    buttons.push_back(&button_black);
    buttons.push_back(&button_increase_pen_size);
    buttons.push_back(&button_decrease_pen_size);

    event_handler.addButton(&button_red);
    event_handler.addButton(&button_yellow);
    event_handler.addButton(&button_blue);
    event_handler.addButton(&button_green);
    event_handler.addButton(&button_pink);
    event_handler.addButton(&button_purple);
    event_handler.addButton(&button_white);
    event_handler.addButton(&button_grey);
    event_handler.addButton(&button_black);
    event_handler.addButton(&button_increase_pen_size);
    event_handler.addButton(&button_decrease_pen_size);

    event_handler.addEvent(SDL_QUIT, exitWindow, reinterpret_cast<void *>(&window_run));
    event_handler.addEvent(BUTTON_SAVE, exitWindow, reinterpret_cast<void *>(&window_run));
    event_handler.addEvent(BUTTON_INCREASE_PEN_SIZE, pen_increase_size, reinterpret_cast<void *>(&change_pen_size));
    event_handler.addEvent(BUTTON_DECREASE_PEN_SIZE, pen_decrease_size, reinterpret_cast<void *>(&change_pen_size));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_RED, pen_change_color, reinterpret_cast<void *>(&color_red));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_YELLOW, pen_change_color, reinterpret_cast<void *>(&color_yellow));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_BLUE, pen_change_color, reinterpret_cast<void *>(&color_blue));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_GREEN, pen_change_color, reinterpret_cast<void *>(&color_green));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_PINK, pen_change_color, reinterpret_cast<void *>(&color_pink));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_PURPLE, pen_change_color, reinterpret_cast<void *>(&color_purple));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_WHITE, pen_change_color, reinterpret_cast<void *>(&color_white));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_GREY, pen_change_color, reinterpret_cast<void *>(&color_grey));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_BLACK, pen_change_color, reinterpret_cast<void *>(&color_black));
    event_handler.addIOEvent(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT, pen_mouse_down_evnt, pen.getMoveState());
    event_handler.addIOEvent(SDL_MOUSEMOTION, SDL_NO_BUTTON, pen_mouse_move_evnt, pen.getMoveState());
    event_handler.addIOEvent(SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT, pen_mouse_up_evnt, pen.getMoveState());

    while (window_run)
    {
        SDL_SetRenderTarget(renderer, nullptr);
        // draw window background
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderFillRect(renderer, &window_background);

        event_handler.run();

        for (auto &button : buttons)
        {
            button->render();
        }

        canvas.render();
        SDL_RenderPresent(renderer);
    }
}