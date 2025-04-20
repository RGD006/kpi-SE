#include <SDL2/SDL.h>
#include "Object.hpp"
#include "EventHandler.hpp"

class Pen
{
private:
    color_t color;
    IObject *shape;

public:
    Pen(color_t);
    Pen(IObject *);
    Pen(color_t, IObject *);
    void changePen(IObject *);
    IObject *getShape();
};