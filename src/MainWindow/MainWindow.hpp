#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "EventHandler.hpp"
#include <SDL2/SDL.h>
#include <stdint.h>
#include <string>

enum exit_status
{
  SUCCESS_EXIT,
  FAILED_EXIT,
  WINDOW_INIT_ERROR,
  SURFACE_INIT_ERROR
};

class MainWindow
{
private:
  SDL_Window *window;
  SDL_Surface *surface;
  uint32_t window_width, window_height, window_background, frame_rate;
  std::string window_title;
  EventHandler event_handler;

public:
  MainWindow(const uint32_t _window_width, const uint32_t _window_height,
             const uint32_t _window_background, const std::string window_title, const uint32_t frame_rate);
  ~MainWindow();
  void setFrameRate(const uint32_t frame_rate);
  exit_status show();
};

#endif