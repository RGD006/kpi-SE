#include <iostream>
#include <SDL2/SDL.h>
#include "MainWindow.hpp"
#include "Rectangle.hpp"

constexpr int32_t window_width = 800, window_height = 800, fps = 60;

int main()
{
  Rectangle rect(50, 50, 50, 50);
  Rectangle bit_rect(200, 150, 100, 100);
  Rectangle Polya(500, 500, 90, 60);

  MainWindow window(window_width, window_height, 0xFFFFFF, "Test", fps);
  window.addObject(&rect);
  window.addObject(&bit_rect);
  window.addObject(&Polya);

  rect.setColor(0x5A42F5);
  bit_rect.setColor(0xFF0000);
  Polya.setColor(0x027512);
  window.show();

  std::cout << "end" << std::endl;
  return 0;
}
