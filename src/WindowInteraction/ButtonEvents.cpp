#include "ButtonEvents.hpp"

void changePenColor(Pen *pen, u32 color)
{
    pen->getShape(createPoint(0, 0))->setColor(color);
}