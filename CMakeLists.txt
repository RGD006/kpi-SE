cmake_minimum_required(VERSION 3.21)
project(bitmap_graphic)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include(FetchContent)
FetchContent_Declare(
    nfd
    GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(nfd)

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
    src/WindowInteraction/Mouse.cpp
    src/EventHandler/Events.cpp
    src/Entity/Entity.cpp
)

set_property(TARGET bitmap_graphic PROPERTY CXX_STANDARD 20)

target_include_directories(bitmap_graphic PRIVATE
    src 
    src/Window 
    src/Object 
    src/EventHandler 
    src/Canvas
    src/Pen                    
    src/Shapes
    src/WindowInteraction
    src/Entity
)

target_include_directories(bitmap_graphic PRIVATE ${nfd_SOURCE_DIR}/src/include)

target_link_libraries(bitmap_graphic PRIVATE SDL2 SDL2_image)
