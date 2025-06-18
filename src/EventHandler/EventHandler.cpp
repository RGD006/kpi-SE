#include "EventHandler.hpp"
#include <iostream>

EventHandler::EventHandler()
{
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
    if (new_event == LISTEN_EVENT_ENTITY)
        listen_always_functions.push_back(event_function_t(function, arg));
    else
        events[new_event].push_back(event_function_t(function, arg));
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
        mouse.pollEvents(&incoming_event);

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

        for (auto &action : listen_always_functions)
        {
            action.function(action.arg);
        }

        // listen if button selected
        for (auto &button : buttons)
        {
            button->listenEvent(mouse);
        }
    }

    mouse.endCallback();
}

SDL_Event EventHandler::getEvent()
{
    return incoming_event;
}

Mouse *EventHandler::getMouse(void)
{
    return &mouse;
}