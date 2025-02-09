#include <iostream>
#include <SDL2/SDL.h>
#include "MainWindow.hpp"

constexpr uint32_t window_width = 800, window_height = 800, fps = 60;

int main()
{
  MainWindow window(window_width, window_height, 0xFFFFFF, "Test", fps);
  window.show();

  std::cout << "end" << std::endl;
  return 0;
}
