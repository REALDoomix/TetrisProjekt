#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>

#include <stdlib.h>
#include <time.h>

#include "game.h"
#include "../../utility/gamemanager/gamemanager.h"
#include "../../utility/textrenderer/textrenderer.h"

static SDL_Rect block;
static Tetromino *current;
static TTF_Font *font;
static SDL_Rect scoreRect;

Tetromino tetrominos[] = {
    {{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 4, {255, 0, 0}},
    {{{1, 1}, {1, 1}, {0, 0}, {0, 0}}, 2, {0, 255, 0}},
    {{{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}, 3, {0, 0, 255}},
    {{{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}, 3, {255, 255, 0}},
    {{{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}, 3, {0, 255, 255}},
    {{{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}, 3, {255, 0, 255}},
    {{{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}, 3, {128, 128, 128}},
};

ActiveTetromino activeTetromino;
int board[BOARD_HEIGHT][BOARD_WIDTH] = {0};
int score;

void init_game_scene()
{
    srand(time(NULL));
    activeTetromino.current = getRandomTetromino();
    activeTetromino.x = BOARD_WIDTH / 2 - 2;
    activeTetromino.y = 0;
    score = 0;
    font = TTF_OpenFont("../font/comicsans.ttf", 128);

    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            board[i][j] = 0;
        }
    }
}

void render_game_scene()
{
    //board rendering
    for (int i = 0; i < BOARD_HEIGHT; i++)
    {
        for (int j = 0; j < BOARD_WIDTH; j++)
        {
            if (board[i][j] != 0)
            {
                block = (SDL_Rect){j * BLOCK_SIZE, i * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE};
                SDL_SetRenderDrawColor(getRenderer(), 200, 200, 200, 255);
                SDL_RenderFillRect(getRenderer(), &block);
            }
        }
    }

    // score rendering
    scoreRect = (SDL_Rect){ 350, 0, 200, 40};
    sdl_draw_score(getRenderer(), font, (SDL_Color){255, 255, 255, 255}, scoreRect, "Score", score);


    // active tetromino rendering
    current = activeTetromino.current;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (current->shape[i][j] != 0)
            {
                SDL_Rect block = {
                    (activeTetromino.x + j) * BLOCK_SIZE,
                    (activeTetromino.y + i) * BLOCK_SIZE,
                    BLOCK_SIZE,
                    BLOCK_SIZE};
                SDL_SetRenderDrawColor(getRenderer(), current->color.r, current->color.g, current->color.b, 255);
                SDL_RenderFillRect(getRenderer(), &block);
            }
        }
    }

    SDL_SetRenderDrawColor(getRenderer(), 50, 50, 50, 255); // grid line rendering
    for (int x = 0; x <= BOARD_WIDTH; x++)
    {
        SDL_RenderDrawLine(getRenderer(), x * BLOCK_SIZE, 0, x * BLOCK_SIZE, BOARD_HEIGHT * BLOCK_SIZE);
    }
    for (int y = 0; y <= BOARD_HEIGHT; y++)
    {
        SDL_RenderDrawLine(getRenderer(), 0, y * BLOCK_SIZE, BOARD_WIDTH * BLOCK_SIZE, y * BLOCK_SIZE);
    }
}

void kill_game_scene()
{
    TTF_CloseFont(font);
}

Tetromino *getRandomTetromino()
{
    return &tetrominos[rand() % 7];
}

void rotateTetromino()
{
    Tetromino rotated = *getCurrent(); // Create a copy of the original Tetromino
    Tetromino *original = getCurrent();

    // Perform the clockwise rotation
    for (int y = 0; y < original->size; y++)
    {
        for (int x = 0; x < original->size; x++)
        {
            rotated.shape[y][x] = original->shape[original->size - x - 1][y];
        }
    }
    if(!checkRotationCollision(activeTetromino.x, activeTetromino.y, &rotated))updateActiveTetrominoShape(&rotated);
}

bool checkFallingCollision(int newX, int newY, Tetromino *fallingTetromino)
{
    for (int y = 0; y < fallingTetromino->size; y++)
    {
        for (int x = 0; x < fallingTetromino->size; x++)
        {
            if (fallingTetromino->shape[y][x])
            {
                int boardX = newX + x;
                int boardY = newY + y;

                // check board border and existing blocks
                if (boardX < 0 || boardX >= BOARD_WIDTH || boardY >= BOARD_HEIGHT || (boardY >= 0 && board[boardY][boardX]))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool checkRotationCollision(int newX, int newY, Tetromino *rotatedTetromino)
{
    for (int y = 0; y < rotatedTetromino->size; y++)
    {
        for (int x = 0; x < rotatedTetromino->size; x++)
        {
            if (rotatedTetromino->shape[y][x])
            {
                int boardX = newX + x; // new X position on the board
                int boardY = newY + y; // new Y position on the board

                // check horizontal collision
                if (boardX < 0 || boardX >= BOARD_WIDTH)
                {
                    return true;
                }

                // check vertical collision
                if (boardY >= BOARD_HEIGHT)
                {
                    return true;
                }

                if (boardY >= 0 && board[boardY][boardX] != 0)
                {
                    return true;
                }
            }
        }
    }

    return false; // No collision detected
}


void updateGame()
{
    static float fallTime = 0;
    fallTime += getDeltaTime();

    if (fallTime >= 0.5f)
    { // fall speed
        if (!checkFallingCollision(activeTetromino.x, activeTetromino.y + 1, getCurrent()))
        {
            activeTetromino.y++;
        }
        else
        {
            // lock current tetromino in place and get a new random one
            for (int y = 0; y < activeTetromino.current->size; y++)
            {
                for (int x = 0; x < activeTetromino.current->size; x++)
                {
                    if (activeTetromino.current->shape[y][x])
                    {
                        int boardX = activeTetromino.x + x;
                        int boardY = activeTetromino.y + y;
                        if (boardY >= 0)
                        {
                            board[boardY][boardX] = 1;
                        }
                    }
                }
            }
            checkAndRemoveFullLines(&score);
            activeTetromino.current = getRandomTetromino();
            activeTetromino.x = BOARD_WIDTH / 2 - 2;
            activeTetromino.y = 0;

            // game over chekcing
            if (checkFallingCollision(activeTetromino.x, activeTetromino.y, getCurrent()))
            {
                setActiveScene(GAME_OVER);
            }
        }
        fallTime = 0;
    }
}

// updates the active tetromino position
void updateActiveTetromino(int x, int y)
{
    activeTetromino.x += x;
    activeTetromino.y += y;
}

// rewrites the shape of the active tetromino with the newShapes shape
void updateActiveTetrominoShape(Tetromino *newShape)
{
    for (int y = 0; y < newShape->size; y++)
    {
        for (int x = 0; x < newShape->size; x++)
        {
            activeTetromino.current->shape[y][x] = newShape->shape[y][x];
        }
    }
}

int getActiveTetrominoPositionX()
{
    return activeTetromino.x;
}

int getActiveTetrominoPositionY()
{
    return activeTetromino.y;
}

// returns the current active tetromino
Tetromino *getCurrent()
{
    return activeTetromino.current;
}

int getScore()
{
    return score;
}

void checkAndRemoveFullLines(int *score)
{
    int fullLines = 0;

    for (int y = BOARD_HEIGHT - 1; y >= 0; y--)
    {
        bool isFull = true;
        // full row checking
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            if (board[y][x] == 0)
            {
                isFull = false;
                break;
            }
        }

        if (isFull)
        {
            fullLines++;

            // move rows above removed row down
            for (int row = y; row > 0; row--)
            {
                for (int col = 0; col < BOARD_WIDTH; col++)
                {
                    board[row][col] = board[row - 1][col];
                }
            }

            // clear top row
            for (int col = 0; col < BOARD_WIDTH; col++)
            {
                board[0][col] = 0;
            }
            y++;
        }
    }
    *score += fullLines;
}