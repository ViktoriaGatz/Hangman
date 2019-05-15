#include "play.h"
#include "names.h"
#include <stdio.h>
#include <time.h>
#define N 30

int Play_Process(SDL_Texture* texture_play, SDL_Renderer* rend) {
    word_t word;
    Get_Word(&word.size, word.string);
    // printf("string: %s\n", word.string);

    if (Word_to_Int(&word.size, word.str, word.string, word.check)) {
        fprintf(stderr, "Word == NULL %s %d\n", __FILE__, __LINE__);
        return -1;
    }

    SDL_Surface** gallows = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 7);
    SDL_Texture** t_gallows = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 7);

    char pwd_1[256] = "./draw/gallows/0.bmp";
    for (unsigned int i = 0; i < 7; i++) {
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
    Draw_Word(&word, rend);
    SDL_RenderPresent(rend);
    SDL_Delay(1000 / 60);
    while (!close_requested) {
        SDL_Event event;
        check_win = Check_Win(word.size, word.check);
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
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
                    close_requested = 1;
                    return 1;
                }
                if (event.key.keysym.scancode >= SDL_SCANCODE_A
                    && event.key.keysym.scancode <= SDL_SCANCODE_Z) {
                    if ((k = Check_Alphavit(
                                 alphavit.size,
                                 alphavit.str,
                                 event.key.keysym.scancode - 3))) {
                        if ((k = Check_Litriche(
                                     word.size,
                                     word.str,
                                     word.check,
                                     event.key.keysym.scancode - 3))
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
                            Draw_Word(&word, rend);
                            SDL_RenderPresent(rend);
                            SDL_Delay(1000 / 60);
                        }
                    } else if (k == -1) {
                        fprintf(stderr,
                                "Alphavit NULL %s %d\n",
                                __FILE__,
                                __LINE__);
                        return -1;
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

int Get_Word(unsigned int* size, char* string) {
    FILE* myfile;
    myfile = fopen("./vocabulary/enimals.txt", "r");
    if (!myfile) {
        fprintf(stderr, "Error myfile\n");
        return -1;
    }
    srand(time(NULL));
    unsigned int n = rand() % N;
    for (unsigned int i = 0; i <= n; i++) {
        fscanf(myfile, "%s\n", string);
        (*size) = strlen(string);
    }
    return 0;
}

int Word_to_Int(unsigned int* size, int* str, char* string, int* check) {
    if (!size || !str || !string || !check) {
        return -1;
    }
    for (unsigned int i = 0; i < (*size); i++) {
        str[i] = string[i] - 96;
    }
    for (unsigned int i = 0; i < (*size); i++) {
        check[i] = 27;
    }
    for (unsigned int i = 0; i < (*size); i++) {
        if (str[i] == str[0]) {
            check[i] = str[0];
        }
        if (str[(*size) - 1] == str[i]) {
            check[i] = str[(*size) - 1];
        }
    }
    // check[0] = str[0];
    // check[(*size) - 1] = str[(*size) - 1];
    return 0;
}

int Check_Alphavit(unsigned int size, int* str, unsigned int c) {
    if (!str) {
        return -1;
    }
    if (c >= size || c <= 0) {
        return 2;
    }
    for (unsigned int i = 0; i < 26; i++) {
        if ((unsigned int)str[i] == c) {
            str[i] = 0;
            return 1;
        }
    }
    return 0;
}

int Check_Litriche(unsigned int size, int* str, int* check, unsigned int c) {
    if (!str || !check) {
        return -1;
    }
    int j = 0;
    for (unsigned int i = 0; i < size; i++) {
        if ((unsigned int)str[i] == c) {
            str[i] = 0;
            check[i] = c;
            j++;
        }
    }
    return j;
}

int Check_Win(unsigned int size, int* check) {
    if (!check) {
        return -1;
    }
    for (unsigned int i = 0; i < size; i++) {
        if (check[i] == 27)
            return 0;
    }
    return 1;
}

void Draw_Word(word_t* word, SDL_Renderer* rend) {
    SDL_Surface** eng_lit = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * 26);
    SDL_Texture** t_eng = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 26);

    char pwd[256] = "./draw/eng/a.bmp";
    for (unsigned int i = 0; i < 26; i++) {
        eng_lit[i] = IMG_Load(pwd);
        t_eng[i] = SDL_CreateTextureFromSurface(rend, eng_lit[i]);
        pwd[11] = 'b' + i;
    }
    SDL_FreeSurface(*eng_lit);
    SDL_Surface* clear = IMG_Load("./draw/clear1.bmp");
    t_eng[26] = SDL_CreateTextureFromSurface(rend, clear);
    SDL_FreeSurface(clear);
    unsigned int i = 0;
    while (i < word->size) {
        ApplySurface(
                (i * 40) + 260, 50, 40, 50, t_eng[word->check[i] - 1], rend);
        i++;
    }
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
