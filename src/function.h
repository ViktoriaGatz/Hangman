#ifndef FUNCTION_H
#define FUNCTION_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define HELLO 100
#define LANGUAGE 200
#define NAME 300
#define MENU 400
#define MODERATORS 500
#define ROT 600
#define PLAY 700
#define WIN 800
#define LOSE 900
#define WAIT_RUS 1000
#define WAIT 1100

void ApplySurface(
        int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* rend);
int Enter_name(SDL_Texture* texture_name, SDL_Window* win, SDL_Renderer* rend);
//деректива препроцессора
#endif
