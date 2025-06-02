#include <iostream>
#include <SDL2/SDL.h>
#include "Window.hpp"


int main()
{
  Window window("Main", 1000, 1000);
  window.run();

  std::cout << "end" << std::endl;

  return 0;
}
