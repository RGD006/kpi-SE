cmake_minimum_required(VERSION 3.21)
project(bitmap_graphic)

find_package(SDL2 REQUIRED)

include_directories(src src/MainWindow src/Object src/EventHandler)

add_executable(bitmap_graphic 
                src/main.cpp
                src/MainWindow/MainWindow.cpp
                src/MainWindow/MainWindow.hpp
                src/Object/Object.cpp
                src/Object/Object.hpp
                src/Rectangle/Rectangle.cpp
                src/Rectangle/Rectangle.hpp
                src/Circle/Circle.cpp
                src/Circle/Circle.hpp
                src/EventHandler/EventHandler.cpp
                src/EventHandler/EventHandler.hpp
) 

set_property(TARGET bitmap_graphic PROPERTY CXX_STANDARD 20)

target_link_libraries(bitmap_graphic SDL2)