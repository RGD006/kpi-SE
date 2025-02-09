cmake_minimum_required(VERSION 3.21)
project(bitmap_graphic)

find_package(SDL2 REQUIRED)

add_executable(bitmap_graphic 
                src/main.cpp
                src/MainWindow/MainWindow.cpp
                src/MainWindow/include/MainWindow.h
)

set_property(TARGET bitmap_graphic PROPERTY CXX_STANDARD 20)

target_link_libraries(bitmap_graphic SDL2)