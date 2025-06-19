#include <Window.hpp>
#include "SDL2/SDL_image.h"
#include "Shapes.hpp"
#include "Pen.hpp"
#include "ButtonEvents.hpp"
#include <iostream>

void exitWindow(void *arg)
{
    *((bool *)arg) = false;
}

Window::Window(const char *window_title, u32 w, u32 h)
    : width(w), height(h)
{
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        std::cerr << "IMG init error " << IMG_GetError() << std::endl;
        exit(EXIT_FAILURE);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    canvas = Canvas(renderer, createPoint(0, 200), 800, 800);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow error:" << SDL_GetError() << "\n";
        exit(EXIT_FAILURE);
    }
}

void sendNewColor(u32 new_color)
{
    SDL_Event change_color_event;
    u32 *send_color = new u32;
    *send_color = new_color;
    change_color_event.type = SDL_USEREVENT;
    change_color_event.user.code = ENTITY_CHANGE_COLOR_ENTITY;
    change_color_event.user.data1 = send_color;
    SDL_PushEvent(&change_color_event);
}

void sendNewInstrument(SDL_Texture *texture)
{
    SDL_Event change_color_event;
    change_color_event.type = SDL_USEREVENT;
    change_color_event.user.code = ENTITY_CHANGE_INSTRUMENT;
    change_color_event.user.data1 = texture;
    SDL_PushEvent(&change_color_event);
}

void Window::run(void)
{
    bool window_run = true;

    SDL_Rect canvas_background = {0};
    SDL_Rect window_background = {
        .x = 0,
        .y = 0,
        .w = width,
        .h = height,
    };

    color_t color_canvas_background(0xFFFFFFFF);

    canvas.setBackground(color_canvas_background, &canvas_background);

    Rectangle *rect = new Rectangle(10, 10, createPoint(0, 0));
    Circle *circ = new Circle(10, createPoint(0, 0), true);

    Entity setted_color(0x00, createRect(0, 0, 0, 0), createRect(500, 0, 50, 50), renderer, "images/border.png");
    ents.push_back(&setted_color);

    auto change_setted_color_entity = [&setted_color](void *arg)
    {
        u32 *new_color = reinterpret_cast<u32 *>(arg);
        if (*new_color != 0x00000000)
        {
            setted_color.setTexture(*new_color);
        }
    };

    Entity setted_instrument(0x00, createRect(0, 0, 0, 0), createRect(500, 50, 50, 50), renderer, "images/border.png");
    ents.push_back(&setted_instrument);

    auto change_setted_instrument_entity = [&setted_instrument](void *arg)
    {
        setted_instrument.setTexture(reinterpret_cast<SDL_Texture *>(arg));
    };
    u32 change_pen_size = 3;

    Button button_red(BUTTON_CHANGE_COLOR_RED, createRect(0, 0, 0, 0), color_button_dest_red, renderer, color_red);
    Button button_yellow(BUTTON_CHANGE_COLOR_YELLOW, createRect(0, 0, 0, 0), color_button_dest_yellow, renderer, color_yellow);
    Button button_blue(BUTTON_CHANGE_COLOR_BLUE, createRect(0, 0, 0, 0), color_button_dest_blue, renderer, color_blue);
    Button button_green(BUTTON_CHANGE_COLOR_GREEN, createRect(0, 0, 0, 0), color_button_dest_green, renderer, color_green);
    Button button_pink(BUTTON_CHANGE_COLOR_PINK, createRect(0, 0, 0, 0), color_button_dest_pink, renderer, color_pink);
    Button button_purple(BUTTON_CHANGE_COLOR_PURPLE, createRect(0, 0, 0, 0), color_button_dest_purple, renderer, color_purple);
    Button button_white(BUTTON_CHANGE_COLOR_WHITE, createRect(0, 0, 0, 0), color_button_dest_white, renderer, color_white);
    Button button_grey(BUTTON_CHANGE_COLOR_GREY, createRect(0, 0, 0, 0), color_button_dest_grey, renderer, color_grey);
    Button button_black(BUTTON_CHANGE_COLOR_BLACK, createRect(0, 0, 0, 0), color_button_dest_black, renderer, color_black);
    Button button_eraser(BUTTON_CHANGE_COLOR_ERASER, createRect(0, 0, 0, 0), color_button_dest_eraser, renderer, "images/eraser.png");
    Button button_increase_pen_size(BUTTON_INCREASE_PEN_SIZE, createRect(0, 0, 0, 0), rect_increase_pen_size, renderer, "images/plus.png");
    Button button_decrease_pen_size(BUTTON_DECREASE_PEN_SIZE, createRect(0, 0, 0, 0), rect_decrease_pen_size, renderer, "images/minus.png");
    Button button_change_shape_rect(BUTTON_CHANGE_SHAPE_RECT, createRect(0, 0, 0, 0), rect_change_pen_rect, renderer, "images/draw_rect.png");
    Button button_change_shape_circ(BUTTON_CHANGE_SHAPE_CIRC, createRect(0, 0, 0, 0), rect_change_pen_circ, renderer, "images/draw_circle.png");
    Button button_set_draw_rect(BUTTON_SET_DRAW_RECTANGLE, createRect(0, 0, 0, 0), rect_set_rectangle_shape, renderer, "images/rectangle.png");
    Button button_set_draw_circ(BUTTON_SET_DRAW_CIRCLE, createRect(0, 0, 0, 0), rect_set_circle_shape, renderer, "images/circle.png");

    Pen pen;
    pen.changeStatus(PEN_STATUS_DRAW_PIXEL);
    pen.changeShape(rect);
    pen.changeColor(0x000000FF);
    pen.addCanvas(&canvas);
    pen.pinMouse(event_handler.getMouse());

    sendNewColor(color_black);
    sendNewInstrument(button_change_shape_rect.getTexture());

    auto pen_listen_mouse = [&pen](void *arg)
    {
        pen.listenEvents(arg);
    };

    auto pen_change_color = [&pen](void *arg)
    {
        if (pen.nowEraser())
        {
            return;
        }

        u32 *new_color = new u32;
        new_color = reinterpret_cast<u32 *>(arg);
        pen.changeColor(*new_color);
        sendNewColor(*new_color);
    };

    auto pen_increase_size = [&pen](void *arg)
    {
        pen.increaseSize(*reinterpret_cast<u32 *>(arg));
    };

    auto pen_decrease_size = [&pen](void *arg)
    {
        pen.decreaseSize(*reinterpret_cast<u32 *>(arg));
    };

    auto pen_set_eraser = [&pen, &rect, &button_eraser](void *arg)
    {
        pen.changeStatus(PEN_STATUS_DRAW_PIXEL);
        pen.changeShape(rect);
        rect->setW(10);
        rect->setH(10);
        pen.changeColor(color_white);
        sendNewColor(color_white);
        sendNewInstrument(button_eraser.getTexture());
    };

    auto pen_change_shape_rect = [&pen, &rect, &button_change_shape_rect](void *arg)
    {
        color_t prev_color;
        if (pen.nowEraser())
        {
            prev_color = color_t(0x000000FF);
            sendNewColor(prev_color);
        }
        else
        {
            prev_color = pen.getShape(createPoint(0, 0))->getColor();
        }
        pen.changeStatus(PEN_STATUS_DRAW_PIXEL);
        rect->setW(10);
        rect->setH(10);
        pen.changeShape(rect);
        pen.changeColor(prev_color);
        sendNewInstrument(button_change_shape_rect.getTexture());
    };

    auto pen_change_shape_circ = [&pen, &circ, &button_change_shape_circ](void *arg)
    {
        color_t prev_color;
        if (pen.nowEraser())
        {
            prev_color = color_t(0x000000FF);
            sendNewColor(prev_color);
        }
        else
        {
            prev_color = pen.getShape(createPoint(0, 0))->getColor();
        }
        pen.changeStatus(PEN_STATUS_DRAW_PIXEL);
        circ->setW(10);
        circ->setH(10);
        pen.changeShape(circ);
        pen.changeColor(prev_color);
        sendNewInstrument(button_change_shape_circ.getTexture());
    };

    auto pen_set_draw_rectangle = [&pen, &rect, &button_set_draw_rect](void *arg)
    {
        if (pen.nowEraser())
        {
            pen.changeColor(color_black);
            sendNewColor(color_black);
        }
        pen.changeStatus(PEN_STATUS_DRAW_SHAPE);
        pen.changeShape(rect);
        sendNewInstrument(button_set_draw_rect.getTexture());
    };

    auto pen_set_draw_circle = [&pen, &circ, &button_set_draw_circ](void *arg)
    {
        if (pen.nowEraser())
        {
            pen.changeColor(color_black);
            sendNewColor(color_black);
        }
        pen.changeStatus(PEN_STATUS_DRAW_SHAPE);
        pen.changeShape(circ);
        sendNewInstrument(button_set_draw_circ.getTexture());
    };

    ents.push_back(&button_red);
    ents.push_back(&button_yellow);
    ents.push_back(&button_blue);
    ents.push_back(&button_green);
    ents.push_back(&button_pink);
    ents.push_back(&button_purple);
    ents.push_back(&button_white);
    ents.push_back(&button_grey);
    ents.push_back(&button_black);
    ents.push_back(&button_eraser);
    ents.push_back(&button_increase_pen_size);
    ents.push_back(&button_decrease_pen_size);
    ents.push_back(&button_change_shape_rect);
    ents.push_back(&button_change_shape_circ);
    ents.push_back(&button_set_draw_rect);
    ents.push_back(&button_set_draw_circ);

    event_handler.addButton(&button_red);
    event_handler.addButton(&button_yellow);
    event_handler.addButton(&button_blue);
    event_handler.addButton(&button_green);
    event_handler.addButton(&button_pink);
    event_handler.addButton(&button_purple);
    event_handler.addButton(&button_white);
    event_handler.addButton(&button_grey);
    event_handler.addButton(&button_black);
    event_handler.addButton(&button_eraser);
    event_handler.addButton(&button_increase_pen_size);
    event_handler.addButton(&button_decrease_pen_size);
    event_handler.addButton(&button_change_shape_rect);
    event_handler.addButton(&button_change_shape_circ);
    event_handler.addButton(&button_set_draw_rect);
    event_handler.addButton(&button_set_draw_circ);

    event_handler.addEvent(ENTITY_CHANGE_INSTRUMENT, change_setted_instrument_entity, nullptr);
    event_handler.addEvent(BUTTON_SET_DRAW_RECTANGLE, pen_set_draw_rectangle, nullptr);
    event_handler.addEvent(BUTTON_SET_DRAW_CIRCLE, pen_set_draw_circle, nullptr);
    event_handler.addEvent(LISTEN_EVENT_ENTITY, pen_listen_mouse, nullptr);
    event_handler.addEvent(ENTITY_CHANGE_COLOR_ENTITY, change_setted_color_entity, nullptr);
    event_handler.addEvent(SDL_QUIT, exitWindow, reinterpret_cast<void *>(&window_run));
    event_handler.addEvent(BUTTON_SAVE, exitWindow, reinterpret_cast<void *>(&window_run));
    event_handler.addEvent(BUTTON_INCREASE_PEN_SIZE, pen_increase_size, reinterpret_cast<void *>(&change_pen_size));
    event_handler.addEvent(BUTTON_DECREASE_PEN_SIZE, pen_decrease_size, reinterpret_cast<void *>(&change_pen_size));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_RED, pen_change_color, reinterpret_cast<void *>(&color_red));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_YELLOW, pen_change_color, reinterpret_cast<void *>(&color_yellow));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_BLUE, pen_change_color, reinterpret_cast<void *>(&color_blue));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_GREEN, pen_change_color, reinterpret_cast<void *>(&color_green));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_PINK, pen_change_color, reinterpret_cast<void *>(&color_pink));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_PURPLE, pen_change_color, reinterpret_cast<void *>(&color_purple));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_WHITE, pen_change_color, reinterpret_cast<void *>(&color_white));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_GREY, pen_change_color, reinterpret_cast<void *>(&color_grey));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_BLACK, pen_change_color, reinterpret_cast<void *>(&color_black));
    event_handler.addEvent(BUTTON_CHANGE_COLOR_ERASER, pen_set_eraser, reinterpret_cast<void *>(&color_eraser));
    event_handler.addEvent(BUTTON_CHANGE_SHAPE_RECT, pen_change_shape_rect, &rect);
    event_handler.addEvent(BUTTON_CHANGE_SHAPE_CIRC, pen_change_shape_circ, &circ);

    while (window_run)
    {
        // draw window background
        SDL_SetRenderDrawColor(renderer, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderFillRect(renderer, &window_background);

        for (auto &button : ents)
        {
            button->render();
        }

        canvas.render();

        event_handler.run();

        SDL_RenderPresent(renderer);
    }
}