#include <iostream>
#include <SDL2/SDL.h>

int main()
{
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) 
  {
    std::cout << "SDL2 ERROR: "<< SDL_GetError() << std::endl;

    return 1;
  }

  std::cout << "Success SDL Init!" << std::endl;

  return 0;
} 