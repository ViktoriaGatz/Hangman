#ifndef PLAY_H
#define PLAY_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

typedef struct word {
    char string[256];
    int str[256];
    int check[256];
    int size;
} word_t;

int Play_Process(
        SDL_Texture* texture_name, SDL_Window* win, SDL_Renderer* rend);
void Get_Word(word_t* word);
void Word_to_Int(word_t* word);
int Check_Litriche(word_t* word, int c);
int Check_Alphavit(word_t* alphavit, int c);
void Draw_Word(
        word_t* word,
        SDL_Texture* texture_play,
        SDL_Window* win,
        SDL_Renderer* rend);
int Check_Win(word_t* word);

#endif
