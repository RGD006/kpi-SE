#include <SDL2/SDL_render.h>
#include <chrono>

class Mouse
{
private:
    SDL_Rect *cursor, *tip;
    int64_t start_click_time_ms, end_click_time_ms;
    bool is_holding; 

    bool is_short_click;
    bool is_long_click;
    
public:
    SDL_Rect* interaction();
    void* mousePressLeft();
    void* mousePressRight();
    void* mouseReleaseLeft();
    void* mouseReleaseRight();
    Mouse();
    ~Mouse();
};