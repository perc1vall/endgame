
#ifndef ENDGAME_TIDY_CODER_HEADER_H
#define ENDGAME_TIDY_CODER_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <zconf.h>
#include <SDL.h>


#if defined(_WIN32) || defined(__CYGWIN__)
#include <SDL_ttf.h>
#elif defined(__linux__)

#include <SDL_ttf.h>

#elif defined(__APPLE__) && defined(__MACH__)
#include <SDL_ttf.h>
#elif defined(unix) || defined(__unix__) || defined(__unix)
#include <SDL_ttf.h>
#else
#endif

#include <SDL_image.h>
#include <SDL_mixer.h>
#include "res_reader.h"


typedef struct check_block {
    int index;
    int type;
} t_check_block;

int
closegame(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect spriteRect,
          SDL_Rect spritePosition, SDL_Texture *backTexture, t_object *obj_arr,
          int countObjects, float scale_y, float scale_x,
          SDL_Texture *back_texture_6,
          SDL_Texture *back_texture_11, SDL_Texture *back_texture_15,
          SDL_Texture *back_texture_17, bool *music_status, int Width,
          int Height
);

typedef struct object_on_map {
    int x1, y1;
    int x2, y2;
    char filepng[20];
    unsigned int type;
    int id;
} obj;

int level0(SDL_Renderer *ren, int Width, int Height, bool *music_status);

void titles(SDL_Renderer *ren, int Width, int Height);

bool insertText(SDL_Renderer *gRenderer, char *textureText, SDL_Color
textColor, int x, int y, int flag);

#endif //ENDGAME_TIDY_CODER_HEADER_H
