#include "../inc/header.h"
#include "../inc/res_reader.h"




int level0(SDL_Renderer *ren, int Width, int Height, bool *music_status) {


    SDL_Surface *image_6 = SDL_LoadBMP("../resource/back_error_6.bmp");
    SDL_Texture *back_texture_6 = SDL_CreateTextureFromSurface(ren, image_6);

    SDL_Surface *image_11 = SDL_LoadBMP("../resource/back_error_11.bmp");
    SDL_Texture *back_texture_11 = SDL_CreateTextureFromSurface(ren, image_11);

    SDL_Surface *image_15 = SDL_LoadBMP("../resource/back_error_15.bmp");
    SDL_Texture *back_texture_15 = SDL_CreateTextureFromSurface(ren, image_15);

    SDL_Surface *image_17 = SDL_LoadBMP("../resource/back_error_17.bmp");
    SDL_Texture *back_texture_17 = SDL_CreateTextureFromSurface(ren, image_17);

    SDL_Surface *image = SDL_LoadBMP("../resource/back.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, image);
    SDL_RenderCopy(ren, texture, NULL, NULL);

    IMG_Init(IMG_INIT_PNG);
    SDL_Texture *spritetexture = IMG_LoadTexture(ren, "../resource/qwe.png");

    SDL_Rect spriteRect;
    SDL_Rect spritePosition;

    int textureWidth, textureHeight;
    SDL_QueryTexture(spritetexture, NULL, NULL, &textureWidth, &textureHeight);

    int h, w, countObjects;
    t_object *arrObjects;

    read_res("../resource/level0.uu", &w, &h, &countObjects,
             &arrObjects);

    float scale_y = (float) Height;
    scale_y /= (float) arrObjects[0].y2;
    float scale_x = (float) Width;
    scale_x*=(float)0.5625;
    scale_x /= (float)arrObjects[0].x2;

    spritePosition.x = 50;
    spritePosition.y = 5;
    spritePosition.w = textureWidth / 3;
    spritePosition.h = (int) (((float) textureHeight / 2) * scale_y);

    spriteRect.x = 0;
    spriteRect.y = textureHeight / 2;
    spriteRect.w = textureWidth / 3;
    spriteRect.h = textureHeight / 2 -15;

    SDL_RenderCopy(ren, spritetexture, &spriteRect, &spritePosition);

    SDL_RenderPresent(ren);
    return closegame(ren, spritetexture, spriteRect, spritePosition, texture,
              arrObjects, countObjects, scale_y, scale_x,  back_texture_6,
              back_texture_11, back_texture_15,
              back_texture_17, music_status,  Width, Height);

}
