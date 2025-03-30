#include <Window.hpp>
#include "Rectangle.hpp"
#include <iostream>

void exitWindow(void *arg)
{
    *((bool *)arg) = false;
    std::cout << "Exit event" << std::endl;
}

Window::Window(const char *window_title, u32 w, u32 h)
{
    window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    canvas = Canvas(window, createPoint(0, 0));
    if (!window)
    {
        std::cerr << "SDL_CreateWindow error:" << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }

}

void Window::run(void)
{
    bool window_run = true;
    Rectangle rect_1(30, 30, createPoint(50, 50));
    rect_1.setColor(color_t(0xfaba11ff));
    Rectangle rect_2(100, 100, createPoint(200, 200));
    canvas.addObject(&rect_1);
    canvas.addObject(&rect_2);
    event_handler.addEvent(SDL_QUIT, exitWindow, reinterpret_cast<void *>(&window_run));

    while (window_run)
    {
        canvas.render();
        event_handler.run();
    }
}