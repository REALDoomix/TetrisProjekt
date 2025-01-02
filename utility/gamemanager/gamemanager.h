#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

enum Scenes {
    MAIN_MENU,
    GAME,
    GAME_OVER
};

typedef struct {
    bool running;
    SDL_Renderer *renderer;
    SDL_Window *window;
    enum Scenes currentScene;
    double deltaTime;
}Game;

void init_game();
void quitGame();
void initRenderer(SDL_Renderer* renderer);
bool isMouseOver(SDL_Rect rect, int x, int y);
bool isRunning();
void updateDeltaTime();
float getDeltaTime();
void setActiveScene(enum Scenes scene);
enum Scenes getCurrentScene();
void renderActiveScene();
SDL_Renderer* getRenderer();