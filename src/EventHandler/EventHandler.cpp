#include "EventHandler.hpp"
#include <iostream>

EventHandler::EventHandler()
{
    auto mouse_down_evnt = [this](void *arg)
    { this->mouse.pressLeft(arg); };
    auto mouse_move_evnt = [this](void *arg)
    { this->mouse.move(arg); };
    auto mouse_up_evnt = [this](void *arg)
    { this->mouse.releaseLeft(arg); };

    addIOEvent(SDL_MOUSEBUTTONDOWN, SDL_BUTTON_LEFT, mouse_down_evnt, nullptr);
    addIOEvent(SDL_MOUSEBUTTONUP, SDL_BUTTON_LEFT, mouse_up_evnt, nullptr);
}

event_function_t::event_function_t()
{
    this->arg = nullptr;
    this->function = nullptr;
}

event_function_t::event_function_t(std::function<void(void *)> function, void *arg)
{
    this->arg = arg;
    this->function = function;
}

event_function_t::event_function_t(std::function<void(void *)> function, void *arg, u32 button)
{
    this->arg = arg;
    this->function = function;
    this->button = button;
}

void EventHandler::addEvent(u32 new_event, std::function<void(void *)> function, void *arg)
{
    // std::cout << "Add event: " << new_event << std::endl;
    events[new_event].push_back(event_function_t(function, arg));
}

void EventHandler::addIOEvent(u32 new_event, u32 button, std::function<void(void *)> function, void *arg)
{
    // std::cout << "Add button event: " << new_event << std::endl;
    io_events[new_event].push_back(event_function_t(function, arg, button));
}

void EventHandler::addButton(Button *button)
{
    buttons.push_back(button);
}

void EventHandler::run(void)
{
    while (SDL_PollEvent(&incoming_event))
    {
        // std::cout << "Event type: " << incoming_event.type << std::endl;
        if (incoming_event.type == SDL_USEREVENT)
        {
            if (events.contains(incoming_event.user.code))
            {
                auto evnt = events.at(incoming_event.user.code);
                for (const auto &action : evnt)
                {
                    action.function(action.arg);
                }
            }
        }
        else if (events.contains(incoming_event.type))
        {
            // std::cout << "Handled event: " << incoming_event.type << std::endl;
            auto evnt = events.at(incoming_event.type);
            for (const auto &action : evnt)
            {
                action.function(action.arg);
            }
        }
        else if (io_events.contains(incoming_event.type))
        {
            // std::cout << "Button handled event: " << incoming_event.type << std::endl;
            auto evnt = io_events.at(incoming_event.type);
            for (const auto &action : evnt)
            {
                if (action.button != SDL_NO_BUTTON && incoming_event.button.button == action.button)
                {
                    action.function(action.arg);
                }
                else if (action.button == SDL_NO_BUTTON)
                {
                    action.function(action.arg);
                }
            }
        }

        /* Mouse events listening*/

        // listen if button selected
        for (auto &button : buttons)
        {
            button->listenMouse(mouse);
        }
    }
}

SDL_Event EventHandler::getEvent()
{
    return incoming_event;
}