#ifndef PLAY_H
#define PLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

int Play_Process(
        SDL_Texture* texture_name, SDL_Window* win, SDL_Renderer* rend);

#endif
