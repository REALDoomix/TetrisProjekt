#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

void sdl_draw_text(SDL_Renderer* renderer, TTF_Font* font, SDL_Color color, SDL_Rect location, const char* text)
{
    // Vykreslení textu se zadaným fontem a barvou do obrázku (surface)
    SDL_Surface* surface = TTF_RenderText_Blended(font, text, color);
    // Převod surface na hardwarovou texturu
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // Vykreslení obrázku
    SDL_RenderCopy(renderer, texture, NULL, &location);

    // Uvolnění textury a surface
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
}