#include <SDL2/SDL.h>
#include <stdbool.h>


#include "../../scenes/mainmenu/mainmenu.h"
#include "./gamemanager.h"
#include "../../scenes/game/game.h"
#include "../../scenes/game_over/game_over.h"


static Game game;

static Uint64 last;
static Uint64 now;

void init_game(){
    init_MainMenu();
    last = SDL_GetPerformanceCounter();
    game.running = true;
    game.currentScene = MAIN_MENU;
}

void updateDeltaTime(){
    now = SDL_GetPerformanceCounter();
    game.deltaTime = (double)((now - last) / (double)SDL_GetPerformanceFrequency());
    last = now;
}

float getDeltaTime(){
    return game.deltaTime;
}

// renderer initialization
void initRenderer(SDL_Renderer* renderer){
    game.renderer = renderer;
}

SDL_Renderer* getRenderer(){
    return game.renderer;
}

int findHighscore(){
    FILE *file = fopen("../leaderboard.txt", "r");
    if(file == NULL){
        printf("Error opening file\n");
        quitGame();
    }
    char buffer[50];
    int highscore = 0;
    while(fgets(buffer, sizeof(buffer), file) != NULL){
        int score = atoi(buffer);
        if(score > highscore){
            highscore = score;
        }
    }
    fclose(file);
    return highscore;
}

// returns the active scene
enum Scenes getCurrentScene(){
    return game.currentScene;
}

// returns running state
bool isRunning(){
    return game.running;
}

// quits the game
void quitGame(){
    switch(game.currentScene){
        case MAIN_MENU:
            init_MainMenu();
            break;
        case GAME:
            init_game_scene();
            break;
        case GAME_OVER:
            init_game_over();
            break;
        default:
            break;
    }
    game.running = false;
}
// checks whether mouse is over a rectangle (used for buttons)
bool isMouseOver(SDL_Rect rect, int x, int y){
    return x >= rect.x && x <= rect.x + rect.w && y >= rect.y && y <= rect.y + rect.h;
}

// scene switching function
void setActiveScene(enum Scenes scene){
    switch(game.currentScene){
        case MAIN_MENU:
            kill_main_menu();
            break;
        case GAME:
            kill_game_scene();
            break;
        case GAME_OVER:
            kill_game_over();
            break;
        default:
            break;
    }
    game.currentScene = scene;
    switch(game.currentScene){
        case MAIN_MENU:
            init_MainMenu();
            break;
        case GAME:
            init_game_scene();
            break;
        case GAME_OVER:
            init_game_over();
            break;
        default:
            break;
    }
}

// renders the active scene
void renderActiveScene(){
    switch (game.currentScene)
    {
    case MAIN_MENU:
        render_main_menu();
        break;
    case GAME:
        render_game_scene();
        updateGame();
        break;
    case GAME_OVER:
        render_game_over();
        break;
    default:
        break;
    }
}

