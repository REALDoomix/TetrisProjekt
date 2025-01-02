#include "leaderboard.h"
#include "../game/game.h"
#include "../../utility/gamemanager/gamemanager.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>


static TTF_Font *font;
static SDL_Rect menu_button_rect;
static FILE *file;



void init_leaderboard() {
    TTF_Init();
    file = fopen("../leaderboard.txt", "r");
    if(file == NULL){
        printf("Error opening file\n");
        quitGame();
    }

    font = TTF_OpenFont("../font/comicsans.ttf", 128);
}

void render_leaderboard(){

}

void kill_leaderboard() {
    TTF_CloseFont(font);
    TTF_Quit();
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }
        if (swapped == false)
            break;
    }
}