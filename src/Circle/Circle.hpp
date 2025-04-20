#include "Object.hpp"
#include "typeof.hpp"

class Circle : public IObject 
{
private:
    u32 radius;    
    bool fill_full; 

public:
    Circle(u32, SDL_Point, bool);
    void drawObject(SDL_Renderer *renderer);
};