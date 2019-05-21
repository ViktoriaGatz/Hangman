#ifndef NAMES_H
#define NAMES_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define HELLO 100
#define NAME 300
#define MENU 400
#define PLAY 700
#define WIN 800
#define LOSE 900

int Enter_name(SDL_Texture* texture_name, SDL_Renderer* rend);
// The preprocessor directive
#endif
