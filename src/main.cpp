#include <iostream>
#include <SDL2/SDL.h>

constexpr uint32_t window_width = 800, window_height = 800, fps = 60;

int main()
{
  SDL_Window *MainWindow = SDL_CreateWindow("bitmap-editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                            window_width, window_height, SDL_WINDOW_SHOWN);
  SDL_Surface *Surface = SDL_GetWindowSurface(MainWindow);
  SDL_Event Event;
  uint32_t color_white = SDL_MapRGB(Surface->format, 255, 255, 255),
           color_black = SDL_MapRGB(Surface->format, 0, 0, 0);
  SDL_Rect Rectangle = {10, 10, 50, 50},
           UpdateWindow = {0, 0, window_width, window_height};
  const uint32_t frame_rate = 1000 / fps;

  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cout << "SDL2 ERROR: " << SDL_GetError() << std::endl;
    return 1;
  }

  std::cout << "Success SDL Init!" << std::endl;

  if (!MainWindow)
  {
    std::cout << "SDL2 ERROR (Window): " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  if (!Surface)
  {
    std::cout << "SDL2 ERROR (Surface): " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(MainWindow);
    SDL_Quit();
    return 1;
  }


  for (;;)
  {
    for (; SDL_PollEvent(&Event);)
    {
      if (Event.type == SDL_QUIT)
      {
        goto EXIT;
      }
    }

    SDL_FillRect(Surface, &UpdateWindow, color_black);
    SDL_FillRect(Surface, &Rectangle, color_white);
    Rectangle.x += 10;
    Rectangle.y += 10;
    SDL_Delay(frame_rate);
    SDL_UpdateWindowSurface(MainWindow);

    if (Rectangle.x + Rectangle.w == window_width)
    {
      Rectangle.x = 0;
    }
    if (Rectangle.y + Rectangle.h == window_height)
    {
      Rectangle.y = 0;
    }
  }

EXIT:

  SDL_DestroyWindow(MainWindow);
  SDL_Quit();
  std::cout << "exit" << std::endl;
  return 0;
}
