#include "play.h"
#include "names.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define N 20

int Play_Process(
        SDL_Texture* texture_play, SDL_Window* win, SDL_Renderer* rend) {
    // Get_Word(string, &word);
    SDL_Delay(5000);
    return 0;
}
/*
double wtime() {
    struct timeval t;
    gettimeofday(&t, NULL);
    return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}
*/
void Get_Word(char* string, word_t* word) {
    FILE* vocabulary;
    vocabulary = fopen(string, "r");
    if (!vocabulary) {
        fprintf(stderr, "Error vocabulary\n");
        return;
    }
    srand(time(NULL));
    int n = rand() % N;
    for (int i = 0; i < n; i++) {
        fscanf(vocabulary, "%s\n", word->string);
        word->size = strlen(word->string);
    }
}
// printf("%s, %d, %d, %d\n", word.string, word.size, word.w, word.h);
