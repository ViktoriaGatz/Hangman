#include "names.h"
#include "play.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

/* clang-format off */
// gcc ./src/play.c `sdl2-config --libs --cflags` -std=c99 -lSDL2_image -lm -o main`
/* clang-format on */

int main() {
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

    char** draw_ = (char**)malloc(sizeof(char[15][256]));

    draw_[0] = "./draw/tor.bmp";
    draw_[1] = "./draw/name.bmp";
    draw_[2] = "./draw/wait_rus.bmp";
    draw_[3] = "./draw/wait.bmp";
    draw_[4] = "./draw/hello.bmp";
    draw_[5] = "./draw/language.bmp";
    draw_[6] = "./draw/play.bmp";
    draw_[7] = "./draw/cursor.bmp";
    draw_[8] = "./draw/lose.bmp";
    draw_[9] = "./draw/win.bmp";

    SDL_Surface** draw = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 10);
    if (!draw) {
        fprintf(stderr, "Error draw\n");
    }
    SDL_Texture** t_draw = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
    if (!t_draw) {
        fprintf(stderr, "Error t_draw\n");
    }
    for (int i = 0; i < 10; i++) {
        draw[i] = IMG_Load((draw_)[i]);
        if (!(draw[i])) {
            fprintf(stderr, "Error create %s", draw_[i]);
            SDL_DestroyRenderer(rend);
            SDL_DestroyWindow(win);
            SDL_Quit();
            return 1;
        }
        t_draw[i] = SDL_CreateTextureFromSurface(rend, draw[i]);
        if (!(t_draw[i])) {
            fprintf(stderr, "Error creating texture: %s\n", SDL_GetError());
            SDL_DestroyRenderer(rend);
            SDL_DestroyWindow(win);
            SDL_Quit();
            return 1;
        }
    }

    free(draw_);
    SDL_FreeSurface(*draw);
    /*
    while (!close_requested) {

      if (poll event) {
        switch(event){
          case SDL_QUIT:
          close_requested = 1;
          break;

        }
      }
    }
    */
    int close_requested = 0;
    int right = 0;
    int left = 1;
    int pos = -1;
    int state = HELLO;
    int del = -1;
    while (!close_requested) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            /*
            int mouse_x, mouse_y;
            int buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
            if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
                close_requested = 1;
            }
            */
            switch (event.type) {
            case SDL_QUIT:
                close_requested = 1;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_KP_ENTER:
                case SDL_SCANCODE_RETURN:
                    if (state == WIN || state == LOSE) {
                        state = PLAY;
                    }
                    if (state == HELLO) {
                        state = NAME;
                    }
                    if (state == MENU && pos == 1) {
                        state = PLAY;
                    }
                    if (state == MENU && pos == 0) {
                        close_requested = 1;
                    }
                    break;
                    if (state == MENU) {
                    case SDL_SCANCODE_A:
                    case SDL_SCANCODE_LEFT:
                        left = 1;
                        right = 0;
                        break;
                    case SDL_SCANCODE_D:
                    case SDL_SCANCODE_RIGHT:
                        right = 1;
                        left = 0;
                        break;
                    }
                case SDL_SCANCODE_ESCAPE:
                    switch (state) {
                    case HELLO:
                        close_requested = 1;
                        break;
                    case MENU:
                    case LOSE:
                    case WIN:
                    case PLAY:
                    case NAME:
                        state = MENU;
                        break;
                    }
                default:
                    break;
                }
            }
            if (state == MENU) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, t_draw[5], NULL, NULL);
                if (left == 1 && right == 0) {
                    ApplySurface(140, 320, 64, 64, t_draw[7], rend);
                    pos = 0;
                }
                if (left == 0 && right == 1) {
                    ApplySurface(360, 320, 64, 64, t_draw[7], rend);
                    pos = 1;
                }
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
            if (state == NAME) {
                state = (Enter_name(t_draw[1], rend) == 0) ? MENU : NAME;
            }

            if (state == PLAY) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, t_draw[6], NULL, NULL);
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
                del = Play_Process(t_draw[6], rend);
                if (del == 0) {
                    state = WIN;
                } else if (del == 2) {
                    state = LOSE;
                } else if (del == 1) {
                    state = MENU;
                }
            }
            if (state == HELLO) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, t_draw[4], NULL, NULL);
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
            if (state == WIN) {
                ApplySurface(20, 180, 600, 150, t_draw[9], rend);
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
            if (state == LOSE) {
                ApplySurface(20, 180, 600, 150, t_draw[8], rend);
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
        }
    }
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    atexit(SDL_Quit);
}
