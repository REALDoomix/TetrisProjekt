#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text);
void sdl_draw_score(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text ,int value);