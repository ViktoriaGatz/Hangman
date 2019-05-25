#ifndef PLAY_H
#define PLAY_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

typedef struct word {
    char string[256];
    int str[256];
    int check[256];
    unsigned int size;
} word_t;

int Play_Process(SDL_Texture* texture_name, SDL_Renderer* rend);
int Get_Word(unsigned int* size, char* string);
int Word_to_Int(unsigned int* size, int* str, char* string, int* check);
int Check_Litriche(unsigned int size, int* str, int* check, unsigned int c);
int Check_Alphavit(unsigned int size, int* str, unsigned int c);
void Draw_Word(word_t* word, SDL_Renderer* rend, int c);
int Check_Win(unsigned int size, int* check);
void ApplySurface(
        int x, int y, int w, int h, SDL_Texture* tex, SDL_Renderer* rend);

#endif
