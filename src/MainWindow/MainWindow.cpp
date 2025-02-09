#include "MainWindow.h"
#include <utility>
#include <stdexcept>

#define SECOND (1000)

MainWindow::MainWindow(const uint32_t _window_width, const uint32_t _window_height,
                       const uint32_t _window_background, const std::string _window_title,
                       const uint32_t frame_rate)
    : window_width(_window_width), window_height(_window_height), window_background(_window_background),
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
}

MainWindow::~MainWindow()
{
  SDL_DestroyWindow(window);
}

void MainWindow::setFrameRate(const uint32_t _frame_rate)
{
  frame_rate = SECOND / _frame_rate;
}

exit_status_e MainWindow::showWindow()
{
  for (;;)
  {
    // TODO: EventHandler

    SDL_Delay(frame_rate);
    SDL_UpdateWindowSurface(window);
  }

  return exit_status_e::SUCCESS_EXIT;
}