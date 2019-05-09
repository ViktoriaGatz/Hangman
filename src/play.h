#ifndef PLAY_H
#define PLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

typedef struct word {
    char string[256];
    int size;
    int x;
    int y;
    int w;
    int h;
} word_t;

int Play_Process(
        SDL_Texture* texture_name, SDL_Window* win, SDL_Renderer* rend);

#endif
