cmake_minimum_required(VERSION 3.21)
project(bitmap-graphic-editor)

find_package(SDL2 REQUIRED)

include_directories(bitmap-graphic-editor/src/MainWindow/include)

add_executable(bitmap-graphic-editor 
                src/main.cpp
                src/MainWindow/MainWindow.cpp
)

set_property(TARGET bitmap-graphic-editor PROPERTY CXX_STANDARD 20)

target_link_libraries(bitmap-graphic-editor SDL2)