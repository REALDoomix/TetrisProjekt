#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../../utility/textrenderer/textrenderer.h"
#include "../../utility/gamemanager/gamemanager.h"


static SDL_Texture* logoTex;
static SDL_Surface* logoS;
static TTF_Font* font;
static int highScore;

static SDL_Rect logo_rect;
static SDL_Rect play_rect;
static SDL_Rect highscore_rect;



void init_MainMenu() {
    TTF_Init();
    highScore = findHighscore();

    logoS = IMG_Load("../images/logo.png");
    logoTex = SDL_CreateTextureFromSurface(getRenderer(), logoS);
    font = TTF_OpenFont("../font/comicsans.ttf", 128);
}

void render_main_menu() {
    SDL_SetRenderDrawColor(getRenderer(), 0, 0, 255, 255);

    logo_rect = (SDL_Rect){ 225, 50, 200, 200 };

    play_rect = (SDL_Rect){ 225, 300, 200, 40 };

    highscore_rect = (SDL_Rect){ 225, 0, 200, 40 };

    SDL_RenderCopy(getRenderer(), logoTex, NULL, &logo_rect);
    SDL_RenderFillRect(getRenderer(), &play_rect);
    sdl_draw_score(getRenderer(), font, (SDL_Color){255, 255, 255, 255}, highscore_rect, "Highscore" ,highScore);
    sdl_draw_text(getRenderer(), font, (SDL_Color){255, 255, 255, 255}, play_rect, "  Play  ");
}

// returns the rect of the main menu button
SDL_Rect get_menu_button_rect(){
    return play_rect;
}

void kill_main_menu() {
    SDL_FreeSurface(logoS);
    TTF_CloseFont(font);
    SDL_DestroyTexture(logoTex);
}