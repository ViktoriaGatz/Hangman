#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)

/*
gcc main.c `sdl2-config --libs --cflags` --std=c99 -Wall -lSDL2_image -lm -o
main
*/

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Not initialized SDL: %s\n", SDL_GetError());
        exit(1);
    }

    SDL_Window* win = SDL_CreateWindow(
            "Hangman",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            0);
    if (!win) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if (!rend) {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* hello = IMG_Load("./draw/hello.bmp");
    if (!hello) {
        printf("error creating hello\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* menu = IMG_Load("./draw/menu.bmp");
    if (!menu) {
        printf("error creating menu\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* cursor = IMG_Load("./draw/cursor.bmp");
    if (!cursor) {
        printf("error creating cursor\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture_hello = SDL_CreateTextureFromSurface(rend, hello);
    SDL_FreeSurface(hello);
    if (!texture_hello) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture_menu = SDL_CreateTextureFromSurface(rend, menu);
    SDL_FreeSurface(menu);
    if (!texture_menu) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture_cursor = SDL_CreateTextureFromSurface(rend, cursor);
    SDL_FreeSurface(cursor);
    if (!texture_cursor) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    int close_requested = 0;
    int enter = 0;
    while (!close_requested) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_KP_ENTER:
                case SDL_SCANCODE_RETURN:
                    enter = 1;
                    break;
                }
                break;
            }
        }
        if (enter == 1) {
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, texture_menu, NULL, NULL);
            SDL_RenderPresent(rend);
            SDL_Delay(1000 / 60);
        } else if (enter == 0) {
            SDL_RenderClear(rend);
            SDL_RenderCopy(rend, texture_hello, NULL, NULL);
            SDL_RenderPresent(rend);
            SDL_Delay(1000 / 60);
        }
    }
    printf("Done\n");
    atexit(SDL_Quit);
}
