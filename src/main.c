#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (480)
#define HELLO 100
#define LANGUAGE 200
#define NAME 300
#define MENU 400
#define MODERATORS 500
#define RT 600
#define PLAY 700
#define WIN 800
#define LOSE 900
#define WAIT_RUS 1000
#define WAIT 1100
/*
gcc main.c `sdl2-config --libs --cflags` --std=c99 -Wall -lSDL2_image -lm -o
main
*/

/*
if (x_pos >= WINDOW_WIDTH - dest.w) x_pos = WINDOW_WIDTH - dest.w;
if (y_pos >= WINDOW_HEIGHT - dest.h) y_pos = WINDOW_HEIGHT - dest.h;
dest.y = (int) y_pos;
dest.x = (int) x_pos;
*/
void ApplySurface(int x, int y, SDL_Texture* tex, SDL_Renderer* rend) {
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w /= 10;
    dest.h /= 8;
    dest.x = x;
    dest.y = y;
    SDL_RenderCopy(rend, tex, NULL, &dest);
}

void Cur_lang(
        int right, int left, SDL_Texture* texture_cursor, SDL_Window* win) {
    if (right == 1 && left == 0) {
    }
    if (right == 0 && left == 1) {
    }
}

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

    SDL_Surface* wait_rus = IMG_Load("./draw/wait_rus.bmp");
    if (!wait_rus) {
        printf("error creating cursor\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texture_wait_rus
            = SDL_CreateTextureFromSurface(rend, wait_rus);
    SDL_FreeSurface(wait_rus);
    if (!texture_wait_rus) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* wait = IMG_Load("./draw/wait.bmp");
    if (!wait) {
        printf("error creating cursor\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texture_wait = SDL_CreateTextureFromSurface(rend, wait);
    SDL_FreeSurface(wait);
    if (!texture_wait_rus) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
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
    SDL_Texture* texture_hello = SDL_CreateTextureFromSurface(rend, hello);
    SDL_FreeSurface(hello);
    if (!texture_hello) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* lang = IMG_Load("./draw/language.bmp");
    if (!lang) {
        printf("error creating lang\n");
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    SDL_Texture* texture_lang = SDL_CreateTextureFromSurface(rend, lang);
    SDL_FreeSurface(lang);
    if (!texture_lang) {
        printf("error creating texture: %s\n", SDL_GetError());
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
    SDL_Texture* texture_cursor = SDL_CreateTextureFromSurface(rend, cursor);
    SDL_FreeSurface(cursor);
    if (!texture_cursor) {
        printf("error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
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
    int enter = 0;
    int right = 0;
    int left = 1;
    int pos = -1;
    int state = MENU;
    while (!close_requested) {
        SDL_Event event;
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                close_requested = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                case SDL_SCANCODE_KP_ENTER:
                case SDL_SCANCODE_RETURN:
                    if (state == MENU) {
                        state = 200;
                        enter = 1;
                    }
                    if (state == LANGUAGE && pos == 1) {
                        state = WAIT;
                    }
                    if (state == LANGUAGE && pos == 0) {
                        state = WAIT_RUS;
                    }
                    break;
                    if (state == LANGUAGE && enter == 1) {
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
                default:
                    break;
                }
            }
            if (state == LANGUAGE) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, texture_lang, NULL, NULL);
                if (left == 1 && right == 0) {
                    ApplySurface(140, 320, texture_cursor, rend);
                    pos = 0;
                }
                if (left == 0 && right == 1) {
                    ApplySurface(360, 320, texture_cursor, rend);
                    pos = 1;
                }
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
            if (state == WAIT_RUS) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, texture_wait_rus, NULL, NULL);
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
            if (state == WAIT) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, texture_wait, NULL, NULL);
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
            if (state == MENU) {
                SDL_RenderClear(rend);
                SDL_RenderCopy(rend, texture_hello, NULL, NULL);
                SDL_RenderPresent(rend);
                SDL_Delay(1000 / 60);
            }
        }
    }

    printf("Done\n");
    atexit(SDL_Quit);
}
