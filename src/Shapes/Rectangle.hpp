#include "Object.hpp"

class Rectangle : public Object
{
private:
public:
    Rectangle(u32, u32, SDL_Point);
    void render(SDL_Renderer *);
};

