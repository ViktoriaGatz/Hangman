#include "function.h"
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

    char user_name[256];
    SDL_Surface* nams = IMG_Load("./draw/name.bmp");

    SDL_Surface* a_eng = IMG_Load("./draw/eng/a.bmp");
    SDL_Texture* texture_a_eng = SDL_CreateTextureFromSurface(rend, a_eng);
    SDL_FreeSurface(a_eng);

    SDL_Surface* b_eng = IMG_Load("./draw/eng/b.bmp");
    SDL_Texture* texture_b_eng = SDL_CreateTextureFromSurface(rend, b_eng);
    SDL_FreeSurface(b_eng);

    SDL_Surface* clear = IMG_Load("./draw/clear.bmp");
    SDL_Texture* texture_clear = SDL_CreateTextureFromSurface(rend, clear);
    SDL_FreeSurface(clear);

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
                        printf("%d\n", (i - 100) / 60);
                        printf("%s\n", user_name);
                        fprintf(RT, "%s\n", user_name);
                        return 0;
                    } else
                        continue;
                case SDL_SCANCODE_A:
                    if (i > 520)
                        break;
                    ApplySurface(i, 240, 40, 50, texture_a_eng, rend);
                    SDL_RenderPresent(rend);
                    SDL_Delay(1000 / 60);
                    user_name[(i - 100) / 60] = 'a';
                    i += 60;
                    break;
                case SDL_SCANCODE_B:
                    if (i > 520)
                        break;
                    ApplySurface(i, 240, 40, 50, texture_b_eng, rend);
                    SDL_RenderPresent(rend);
                    SDL_Delay(1000 / 60);
                    user_name[(i - 100) / 60] = 'b';
                    i += 60;
                    break;
                case SDL_SCANCODE_BACKSPACE:
                    i = (i == 100) ? 100 : i - 60;
                    ApplySurface(i, 240, 40, 50, texture_clear, rend);
                    SDL_RenderPresent(rend);
                    SDL_Delay(1000 / 60);
                    break;
                default:
                    break;
                }
            default:
                break;
            }
        }
    }
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
