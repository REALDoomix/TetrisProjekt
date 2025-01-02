#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void init_game_over();
void render_game_over();
void kill_game_over();
SDL_Rect get_gameover_button_rect();
void writeScoreToFile();