#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include "../utility/textrenderer.h"

void render_main_menu(SDL_Renderer* renderer) {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    SDL_Surface* logoS = IMG_Load("../images/logo.png");
    SDL_Texture* logoTex = SDL_CreateTextureFromSurface(renderer, logoS);
    TTF_Font* font = TTF_OpenFont("../fonts/comicsans.ttf", 24);
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    SDL_Rect logo_rect = { 640-100, 50, 200, 200 };

    SDL_Rect play_rect = { 640-100, 300, 200, 40 };

    SDL_RenderCopy(renderer, logoTex, NULL, &logo_rect);
    SDL_RenderFillRect(renderer, &play_rect);
    sdl_draw_text(renderer, font, (SDL_Color){255, 0, 0, 255}, play_rect, "Play");
    SDL_RenderPresent(renderer);


    SDL_FreeSurface(logoS);
    TTF_CloseFont(font);
    
    SDL_DestroyTexture(logoTex);
}