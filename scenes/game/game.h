#pragma once

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "../../utility/gamemanager/gamemanager.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20
#define BLOCK_SIZE 30


typedef struct {
    int shape[4][4];
    int size;
    SDL_Color color;
}Tetromino;

typedef struct{
    Tetromino *current;
    int x;
    int y;
} ActiveTetromino;

bool checkFallingCollision(int newX, int newY, Tetromino *fallingTetromino);
bool checkRotationCollision(int newX, int newY, Tetromino *rotatedTetromino);


int getScore();
void init_game_scene();
void render_game_scene();
void kill_game_scene();
void updateGame();
void updateActiveTetromino(int x, int y);
int getActiveTetrominoPositionX();
int getActiveTetrominoPositionY();
void rotateTetromino();
Tetromino *getCurrent();
void updateActiveTetrominoShape(Tetromino *newShape);
Tetromino *getRandomTetromino();
void checkAndRemoveFullLines(int *score);