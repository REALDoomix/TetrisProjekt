#include <SDL2/SDL.h>

#include "../utility/gamemanager/gamemanager.h"
#include "../scenes/game/game.h"
#include "../scenes/mainmenu/mainmenu.h"
#include "../scenes/game_over/game_over.h"

void event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            exit(0);
            break;

        case SDL_MOUSEBUTTONDOWN:
            //left click handling
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                //button checking
                if(isMouseOver(get_menu_button_rect(),event.motion.x, event.motion.y) && getCurrentScene() == MAIN_MENU){
                    setActiveScene(GAME);
                } else if (isMouseOver(get_gameover_button_rect(), event.motion.x, event.motion.y) && getCurrentScene() == GAME_OVER){
                setActiveScene(MAIN_MENU);
                }
            }
            break;

        case SDL_KEYDOWN:
            if(getCurrentScene() == GAME){
                switch (event.key.keysym.sym)
            {
            case SDLK_LEFT:
                if (!checkFallingCollision(getActiveTetrominoPositionX() - 1, getActiveTetrominoPositionY(), getCurrent()))
                    updateActiveTetromino(-1, 0);
                break;
            case SDLK_RIGHT:
                if (!checkFallingCollision(getActiveTetrominoPositionX() + 1, getActiveTetrominoPositionY(), getCurrent()))
                    updateActiveTetromino(1, 0);
                break;
            case SDLK_DOWN:
                if (!checkFallingCollision(getActiveTetrominoPositionX(), getActiveTetrominoPositionY() + 1, getCurrent()))
                    updateActiveTetromino(0, 1);
                break;
            case SDLK_UP:
                rotateTetromino();
            }
            }
            break;

        default:
            break;
        }
    }
}