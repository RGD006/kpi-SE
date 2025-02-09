#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "EventHandler.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include <list>
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
  int32_t window_width, window_height, frame_rate;
  uint32_t window_background;
  std::string window_title;
  EventHandler event_handler;
  std::list<Object *> objects;

public:
  MainWindow(const int32_t _window_width, const int32_t _window_height,
             const uint32_t _window_background, const std::string window_title, const int32_t frame_rate);
  ~MainWindow();
  void setFrameRate(const int32_t frame_rate);
  exit_status show();
  void addObject(Object *object);
};

#endif