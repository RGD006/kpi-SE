#pragma once 

#include "Object.hpp"
#include "typeof.hpp"

class Circle : public IObject 
{
private:
    u32 radius;    
    bool fill_full; 

public:
    Circle(u32, SDL_Point, bool);
    void setW(u32 value);
    void setH(u32 value);
    u32 getW(void);
    u32 getH(void);
    void drawObject(SDL_Renderer *renderer);
};