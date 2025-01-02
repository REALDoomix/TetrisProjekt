#include "game_over.h"
#include "../game/game.h"


#include "../../utility/textrenderer/textrenderer.h"
#include "../game/game.h"

static TTF_Font *font;
static SDL_Rect menu_button_rect;

void init_game_over() {
    TTF_Init();
    writeScoreToFile();
    font = TTF_OpenFont("../font/comicsans.ttf", 128);
}

void render_game_over(){
    SDL_Rect titleRect = { 100, 50, 400, 200 };
    SDL_Rect scoreRect = { 200, 300, 200, 40 };
    menu_button_rect = (SDL_Rect){ 200, 400, 200, 40 };
    sdl_draw_text(getRenderer(), font, (SDL_Color){255, 255, 255, 255}, titleRect, "Game over!");
    sdl_draw_score(getRenderer(), font, (SDL_Color){255, 255, 255, 255}, scoreRect, "Score" , getScore());
    SDL_RenderFillRect(getRenderer(), &menu_button_rect);
    sdl_draw_text(getRenderer(), font, (SDL_Color){255, 255, 255, 255}, menu_button_rect, "Back to menu");

}

// returns the rect of the game over buttion
SDL_Rect get_gameover_button_rect(){
    return (SDL_Rect)menu_button_rect;
}

void writeScoreToFile(){
    FILE *file = fopen("../leaderboard.txt", "a");
    if(file == NULL){
        printf("Error opening file\n");
        quitGame();
    }
    fprintf(file, "%d\n", getScore());
    fclose(file);
}

void kill_game_over() {
    TTF_CloseFont(font);
    TTF_Quit();
}