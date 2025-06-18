#pragma once

#include "Object.hpp"
#include "typeof.hpp"

class Circle : public Object 
{
private:
    u32 radius_x;
    u32 radius_y;
    bool fill_full;

public:
    Circle(u32 r, SDL_Point center_point, bool filled = false);
    Circle(u32 rx, u32 ry, SDL_Point center_point, bool filled = false); // эллипс

    void setW(i32 value) override;
    void setH(i32 value) override;
    i32 getW(void) override;
    i32 getH(void) override;

    void drawObject(SDL_Renderer *renderer) override;
};
