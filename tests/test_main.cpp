#include <gtest/gtest.h>
#include <SDL2/SDL.h>
#include "Canvas.hpp"
#include "Pen.hpp"
#include "Button.hpp"
#include "EventHandler.hpp"
#include "Events.hpp"

class SDLTestEnvironment : public ::testing::Environment {
public:
    void SetUp() override {
        if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
            std::exit(1);
        }
    }

    void TearDown() override {
        SDL_Quit();
    }
};

class SDLMock {
public:
    static SDL_Renderer* MockRenderer() {
        SDL_Window* window = SDL_CreateWindow("test", 0, 0, 100, 100, SDL_WINDOW_HIDDEN);
        if (!window) {
            fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
            std::exit(1);
        }

        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
        if (!renderer) {
            fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
            SDL_DestroyWindow(window);
            std::exit(1);
        }

        return renderer;
    }
};

TEST(CanvasTest, CanSetAndGetCanvasTexture) {
    SDL_Renderer* renderer = SDLMock::MockRenderer();
    Canvas canvas(renderer, {0, 0}, 100, 100);
    SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET, 100, 100);
    canvas.setCanvasTexture(tex);
    EXPECT_EQ(canvas.getCanvasTexture(), tex);

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(renderer);
}

TEST(PenTest, StatusChangeWorks) {
    Pen pen;
    pen.changeStatus(PEN_STATUS_FILL);
    EXPECT_EQ(pen.getStatus(), PEN_STATUS_FILL);
}

TEST(PenTest, NowEraserWorks) {
    Pen pen;
    pen.changeColor(color_black);
    EXPECT_FALSE(pen.nowEraser());
    pen.changeColor(color_white);
    EXPECT_TRUE(pen.nowEraser());
}

TEST(ButtonTest, ConstructWithColorDoesNotCrash) {
    SDL_Renderer* renderer = SDLMock::MockRenderer();
    EXPECT_NO_THROW({
        Button btn(1, {0, 0, 50, 50}, {0, 0, 50, 50}, renderer, 0xFF00FF);
    });
    SDL_DestroyRenderer(renderer);
}

TEST(EventHandlerTest, AddAndRunEvents) {
    EventHandler handler;
    bool called = false;
    handler.addEvent(123, [&](void*) { called = true; }, nullptr);

    SDL_Event fake_event;
    fake_event.type = 123;
    SDL_PushEvent(&fake_event);

    handler.run();
    EXPECT_TRUE(called);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::AddGlobalTestEnvironment(new SDLTestEnvironment);
    return RUN_ALL_TESTS();
}
