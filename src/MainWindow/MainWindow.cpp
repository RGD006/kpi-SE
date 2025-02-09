#include "MainWindow.hpp"
#include <utility>
#include <stdexcept>
#include <iostream>

#define SECOND (1000)

MainWindow::MainWindow(const int32_t _window_width, const int32_t _window_height,
                       const uint32_t _window_background, const std::string _window_title,
                       const int32_t frame_rate)
    : window_width(_window_width), window_height(_window_height),
      window_title(std::move(_window_title)), frame_rate(SECOND / frame_rate)
{
  window = SDL_CreateWindow(window_title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                            window_width, window_height, SDL_WINDOW_SHOWN);

  surface = SDL_GetWindowSurface(window);

  if (!window)
  {
    throw WINDOW_INIT_ERROR;
    SDL_Quit();
  }

  if (!surface)
  {
    throw SURFACE_INIT_ERROR;
    SDL_DestroyWindow(window);
    SDL_Quit();
  }

  window_background = SDL_MapRGB(surface->format,
                                 ((_window_background >> 16) & 0xFF),
                                 ((_window_background >> 8) & 0xFF),
                                 (_window_background & 0xFF));
}

MainWindow::~MainWindow()
{
  SDL_DestroyWindow(window);
}

void MainWindow::addObject(Object *object)
{
  object->setSurface(surface);
  objects.emplace_back(object);
}

void MainWindow::setFrameRate(const int32_t _frame_rate)
{
  frame_rate = SECOND / _frame_rate;
}

exit_status MainWindow::show()
{
  SDL_Rect frame_background = {.x = 0, .y = 0, .w = window_width, .h = window_height};

  for (;;)
  {
    int32_t event_type = event_handler.getEvent();
    if (event_type == SDL_QUIT)
    {
      break;
    }
    else if (event_type == INT32_MAX)
    {
      std::cerr << "Unhandled event" << std::endl;
      break;
    }

    // update buffer
    SDL_FillRect(surface, &frame_background, window_background);

    for (auto object : objects)
    {
      object->showObject();
    }

    SDL_Delay(frame_rate);
    SDL_UpdateWindowSurface(window);
  }

  return exit_status::SUCCESS_EXIT;
}