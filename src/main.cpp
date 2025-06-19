#include <iostream>
#include <SDL2/SDL.h>
#include "Window.hpp"

int main()
{
  Window window("Painter", 1000, 1000);
  window.run();
  std::cout << "stop" << std::endl;

  return 0;
}
