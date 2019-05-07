#include "names.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>

int Enter_name(SDL_Texture* texture_name, SDL_Window* win, SDL_Renderer* rend) {
    FILE* RT;
    RT = fopen("./log/table_of_records.dat", "a+b");
    if (!RT) {
        return 1;
    }

    SDL_Surface** eng_lit = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 26);
    SDL_Texture** t_eng = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 26);

    char pwd[256] = "./draw/eng/a.bmp";
    for (int i = 0; i < 26; i++) {
        eng_lit[i] = IMG_Load(pwd);
        t_eng[i] = SDL_CreateTextureFromSurface(rend, eng_lit[i]);
        pwd[11] = 'b' + i;
    }
    SDL_FreeSurface(*eng_lit);
    SDL_Surface* clear = IMG_Load("./draw/clear.bmp");
    SDL_Texture* texture_clear = SDL_CreateTextureFromSurface(rend, clear);
    SDL_FreeSurface(clear);

    char* user_name = (char*)malloc(sizeof(char) * 20);
    int close_requested = 0;
    int i = 100;
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, texture_name, NULL, NULL);
    SDL_RenderPresent(rend);
    SDL_Delay(1000 / 60);
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
                    if (i > 100) {
                        user_name[(i - 100) / 60] = '\0';
                        return 0;
                    } else
                        continue;
                case SDL_SCANCODE_BACKSPACE:
                    i = (i == 100) ? 100 : i - 60;
                    ApplySurface(i, 240, 40, 50, texture_clear, rend);
                    SDL_RenderPresent(rend);
                    SDL_Delay(1000 / 60);
                    break;
                default:
                    if (event.key.keysym.scancode >= SDL_SCANCODE_A
                        && event.key.keysym.scancode <= SDL_SCANCODE_Z) {
                        if (i > 520)
                            break;
                        ApplySurface(
                                i,
                                240,
                                40,
                                50,
                                t_eng[event.key.keysym.scancode - 4],
                                rend);
                        user_name[(i - 100) / 60]
                                = 'a' + event.key.keysym.scancode - 4;
                        SDL_RenderPresent(rend);
                        SDL_Delay(1000 / 60);
                        i += 60;
                    }
                    break;
                }
            default:
                break;
            }
        }
    }
    fclose(RT);
    return 0;
}

void ApplySurface(
        int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* rend) {
    SDL_Rect dest;
    SDL_QueryTexture(tex, NULL, NULL, &dest.w, &dest.h);
    dest.w = w;
    dest.h = h;
    dest.x = x;
    dest.y = y;
    SDL_RenderCopy(rend, tex, NULL, &dest);
}
