#include <iostream>
#include <SDL2/SDL.h>
#include "Window.hpp"


int main()
{
  Window window("Main", 500, 500);
  window.run();

  std::cout << "end" << std::endl;

  return 0;
}
