#include "play.h"
#include "names.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <time.h>
#define N 30

int Play_Process(
        SDL_Texture* texture_play, SDL_Window* win, SDL_Renderer* rend) {
    word_t word;
    Get_Word(&word);
    printf("string: %s\n", word.string);
    Word_to_Int(&word);

    SDL_Surface** gallows = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 7);
    SDL_Texture** t_gallows = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 7);

    char pwd_1[256] = "./draw/gallows/0.bmp";
    for (int i = 0; i < 7; i++) {
        gallows[i] = IMG_Load(pwd_1);
        t_gallows[i] = SDL_CreateTextureFromSurface(rend, gallows[i]);
        pwd_1[15] = '1' + i;
    }
    SDL_FreeSurface(*gallows);

    word_t alphavit;
    for (int j = 0; j < 26; j++) {
        alphavit.str[j] = j + 1;
    }
    int check_win = 0;
    int k = 0;
    int proc_l = 0;
    int close_requested = 0;
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, texture_play, NULL, NULL);
    ApplySurface(20, 20, 200, 225, t_gallows[proc_l], rend);
    Draw_Word(&word, texture_play, win, rend);
    SDL_RenderPresent(rend);
    SDL_Delay(1000 / 60);
    while (!close_requested) {
        SDL_Event event;
        check_win = Check_Win(&word);
        if (check_win == 1) {
            SDL_Delay(1000 / 60);
            return 0;
        }
        if (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                close_requested = 1;
                return 1;
            case SDL_KEYDOWN:
                if (event.key.keysym.scancode >= SDL_SCANCODE_A
                    && event.key.keysym.scancode <= SDL_SCANCODE_Z) {
                    if (Check_Alphavit(
                                &alphavit, event.key.keysym.scancode - 3)) {
                        if ((k = Check_Litriche(
                                     &word, event.key.keysym.scancode - 3))
                            == 0) {
                            proc_l++;
                            ApplySurface(
                                    20, 20, 200, 225, t_gallows[proc_l], rend);
                            SDL_RenderPresent(rend);
                            SDL_Delay(1000 / 60);
                            if (proc_l == 6) {
                                SDL_Delay(1000 / 60);
                                return 2;
                            }
                            break;
                        } else if (k > 0) {
                            Draw_Word(&word, texture_play, win, rend);
                            SDL_RenderPresent(rend);
                            SDL_Delay(1000 / 60);
                        }
                    } else {
                        break;
                    }
                }
            default:
                break;
            }
        }
    }
    return 0;
}

void Get_Word(word_t* word) {
    FILE* myfile;
    myfile = fopen("./vocabulary/enimals.txt", "r");
    if (!myfile) {
        fprintf(stderr, "Error myfile\n");
        return;
    }
    srand(time(NULL));
    int n = rand() % N;
    for (int i = 0; i <= n; i++) {
        fscanf(myfile, "%s\n", word->string);
        word->size = strlen(word->string);
    }
}

void Word_to_Int(word_t* word) {
    for (int i = 0; i < word->size; i++) {
        word->str[i] = word->string[i] - 96;
    }
    for (int i = 0; i < word->size; i++) {
        word->check[i] = 27;
    }
    word->check[0] = word->str[0];
    word->check[word->size - 1] = word->str[word->size - 1];
}

int Check_Alphavit(word_t* alphavit, int c) {
    for (int i = 0; i < 26; i++) {
        if (alphavit->str[i] == c) {
            alphavit->str[i] = 0;
            return 1;
        }
    }
    return 0;
}

int Check_Litriche(word_t* word, int c) {
    int j = 0;
    for (int i = 0; i < word->size; i++) {
        if (word->str[i] == c) {
            word->str[i] = 0;
            word->check[i] = c;
            j++;
        }
    }
    return j;
}

void Draw_Word(
        word_t* word,
        SDL_Texture* texture_play,
        SDL_Window* win,
        SDL_Renderer* rend) {
    SDL_Surface** eng_lit = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 26);
    SDL_Texture** t_eng = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 26);

    char pwd[256] = "./draw/eng/a.bmp";
    for (int i = 0; i < 26; i++) {
        eng_lit[i] = IMG_Load(pwd);
        t_eng[i] = SDL_CreateTextureFromSurface(rend, eng_lit[i]);
        pwd[11] = 'b' + i;
    }
    SDL_FreeSurface(*eng_lit);
    SDL_Surface* clear = IMG_Load("./draw/clear1.bmp");
    t_eng[26] = SDL_CreateTextureFromSurface(rend, clear);
    SDL_FreeSurface(clear);
    int i = 0;
    while (i < word->size) {
        ApplySurface(
                (i * 40) + 260, 50, 40, 50, t_eng[word->check[i] - 1], rend);
        i++;
    }
}

int Check_Win(word_t* word) {
    for (int i = 0; i < word->size; i++) {
        if (word->check[i] == 27)
            return 0;
    }
    return 1;
}
