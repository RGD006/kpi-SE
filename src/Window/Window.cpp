#include <Window.hpp>
#include "Rectangle.hpp"
#include <Circle.hpp>
#include <iostream>

void exitWindow(void *arg)
{
    *((bool *)arg) = false;
    std::cout << "Exit event" << std::endl;
}

Window::Window(const char *window_title, u32 w, u32 h)
    : width(w), height(h)
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
    Rectangle background(width, height, createPoint(0, 0));
    
    Circle cicrle(50, (SDL_Point){100, 100}, false);
    cicrle.setColor(0xcf1b1b);
    canvas.addObject(&cicrle);

    event_handler.addEvent(SDL_QUIT, exitWindow, reinterpret_cast<void *>(&window_run));

    while (window_run)
    {
        canvas.render();
        event_handler.run();
    }
} 