cmake_minimum_required(VERSION 3.21)
project(bitmap_graphic)

find_package(SDL2 REQUIRED)

include_directories(src 
                    src/Window 
                    src/Object 
                    src/EventHandler 
                    src/Canvas
                    src/Pen                    
                    src/Shapes
                    src/WindowInteraction
)

add_executable(bitmap_graphic 
                src/main.cpp
                src/Window/Window.cpp
                src/Object/Object.cpp
                src/Shapes/Rectangle.cpp
                src/Shapes/Circle.cpp
                src/EventHandler/EventHandler.cpp
                src/Canvas/Canvas.cpp
                src/Pen/Pen.cpp
                src/WindowInteraction/Button.cpp
) 

set_property(TARGET bitmap_graphic PROPERTY CXX_STANDARD 20)

target_link_libraries(bitmap_graphic SDL2)