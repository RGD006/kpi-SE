cmake_minimum_required(VERSION 3.21)
project(bitmap_graphic)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include(FetchContent)
FetchContent_Declare(
    nfd
    GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
    GIT_TAG        master
)
FetchContent_MakeAvailable(nfd)

add_library(nfd
    ${nfd_SOURCE_DIR}/src/nfd_common.c
    ${nfd_SOURCE_DIR}/src/nfd_gtk.c
)

target_include_directories(nfd PUBLIC
    ${nfd_SOURCE_DIR}/src/include
    ${GTK3_INCLUDE_DIRS}
)

target_compile_options(nfd PRIVATE ${GTK3_CFLAGS_OTHER})

# Дуже важливо: лінкувати nfd з GTK3
target_link_libraries(nfd PRIVATE ${GTK3_LIBRARIES})

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

target_link_libraries(bitmap_graphic PRIVATE
    SDL2 SDL2_image
    nfd
)
