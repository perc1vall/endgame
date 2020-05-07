#include "../inc/header.h"
#include "../inc/res_reader.h"


const int FRAMES_COUNT = 6;
const int STEPS_PER_FRAME = 2;

const int PLAYER_NOT_ON_BLOCK = 0;
const int PLAYER_ON_BLOCK = 1;
const int PLAYER_ON_ERROR = 2;

SDL_Keycode side = SDLK_RIGHT;

SDL_Texture *
loadIMG(char *path, SDL_Renderer *gRenderer) {
    IMG_Init(IMG_INIT_PNG);
    SDL_Texture *texture = IMG_LoadTexture(gRenderer, path);
    if (texture == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path,
               IMG_GetError());
    }
    return texture;
}

bool
insertTexture(SDL_Renderer *gRenderer, SDL_Texture *gTexture, int x, int y,
              int width, int height) {
    SDL_Rect position;
    position.x = x;
    position.y = y;
    position.w = width;
    position.h = height;
    SDL_RenderCopy(gRenderer, gTexture, NULL, &position);
    return true;
}

bool insertText2(TTF_Font *gFont, SDL_Renderer *gRenderer,
                char *textureText, SDL_Color textColor, int x,
                int y) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText,
                                                    textColor);
    if (textSurface == NULL) {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",
               TTF_GetError());
        return false;
    }
    SDL_Texture *mTexture = SDL_CreateTextureFromSurface(gRenderer,
                                                         textSurface);
    if (mTexture == NULL) {
        printf("Unable to create texture from rendered text! SDL Error: %s\n",
               SDL_GetError());
        return false;
    }
    SDL_Rect position;
    position.x = x;
    position.y = y;
    position.w = textSurface->w;
    position.h = textSurface->h;
    SDL_FreeSurface(textSurface);
    SDL_RenderCopy(gRenderer, mTexture, NULL, &position);
    return mTexture != NULL;
}

t_check_block
checkOnBlocks(const t_object *obj_arr, const SDL_Rect spritePosition,
              int countObjects, float scale_y, float scale_x) {
    bool onError = false;
    bool onBlock = false;
    t_check_block checkBlock;
    for (int i = 0; i < countObjects; i++) {
        if (side == SDLK_RIGHT) {
            if (obj_arr[i].type == 0 || obj_arr[i].type == 2) {
                if (spritePosition.y + spritePosition.h ==
                    (int) (scale_y * (float) obj_arr[i].y2) &&
                    spritePosition.x - 23 + spritePosition.w <=
                    (int) (scale_x * (float) obj_arr[i].x2 + 23) &&
                    spritePosition.x + 23 >
                    (int) (scale_x * (float) obj_arr[i].x1)) {
                    if (obj_arr[i].type == 2) {
                        onError = true;
                        checkBlock.index = i;
                    }
                    onBlock = true;
                    break;
                }
            }
        } else if (side == SDLK_LEFT) {
            if (obj_arr[i].type == 0 || obj_arr[i].type == 2) {
                if (spritePosition.y + spritePosition.h ==
                    (int) (scale_y * (float) obj_arr[i].y2) &&
                    spritePosition.x - 23 + spritePosition.w <=
                    (int) (scale_x * (float) obj_arr[i].x2 + 23) &&
                    spritePosition.x + 23 >
                    (int) (scale_x * (float) obj_arr[i].x1 - 23)) {
                    if (obj_arr[i].type == 2) {
                        onError = true;
                        checkBlock.index = i;
                    }
                    onBlock = true;
                    break;
                }
            }
        }

    }
    if (!onBlock) {
        if (spritePosition.y + spritePosition.h >=
            (int) (scale_y * (float) obj_arr[0].y2))
            onBlock = true;
    }
    if (onBlock && onError) {
        checkBlock.type = PLAYER_ON_ERROR;
    } else if (onBlock) {
        checkBlock.type = PLAYER_ON_BLOCK;
    } else checkBlock.type = PLAYER_NOT_ON_BLOCK;
    return checkBlock;
}

void
renderStep(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect spriteRect,
           SDL_Rect spritePosition, SDL_Texture *backTexture,
           t_object *obj_arr, int countObjects, float scale_y,
           float scale_x, SDL_Texture *back_texture_6,
           SDL_Texture *back_texture_11, SDL_Texture *back_texture_15,
           SDL_Texture *back_texture_17, bool tab, int Width, int Height) {
    t_check_block checkError = checkOnBlocks(obj_arr, spritePosition,
                                             countObjects, scale_y, scale_x);
    SDL_Texture *back_texture = backTexture;
    if (checkError.type == PLAYER_ON_ERROR) {
        switch (checkError.index) {
            case 6:
                back_texture = back_texture_6;
                break;
            case 11:
                back_texture = back_texture_11;
                break;
            case 15:
                back_texture = back_texture_15;
                break;
            case 17:
                back_texture = back_texture_17;
                break;
        }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, back_texture, NULL, NULL);
    SDL_Rect rect;
    rect.x = (int)((float)Width*0.5625);
    rect.y = 0;
    rect.w = Width - rect.x;
    rect.h = Height;
    SDL_Color bg = {25, 26, 36, 255};
    if (tab) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
        TTF_Init();
        TTF_Font *arial_font = TTF_OpenFont("../resource/ArialBlack.ttf", Height / 40);
        SDL_Color textColor = {50, 1, 50};
        insertText2(arial_font, renderer, "", textColor, 3 * Width / 4,
                   290 / 4 + 14);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_Texture *stacklogo = loadIMG("../resource/stacklogo.png", renderer);
        insertTexture(renderer, stacklogo, rect.x, rect.y, 895 / 4, 290 / 4);
        TTF_Quit();
    } else {
        SDL_SetRenderDrawColor(renderer, bg.r, bg.g, bg.b, bg.a);
        SDL_RenderFillRect(renderer, &rect);
        SDL_RenderDrawRect(renderer, &rect);
    }

    SDL_RenderCopy(renderer, texture, &spriteRect, &spritePosition);
    SDL_RenderPresent(renderer);
    SDL_Delay(16);
}

void
renderSteps(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect *spriteRect,
            SDL_Rect *spritePosition,
            SDL_Texture *backTexture, int frameWidth, int frameHeight,
            int textureWidth, int textureHeight,
            SDL_Keycode key, t_object *obj_arr, int countObjects,
            float scale_y, float scale_x, SDL_Texture *back_texture_6,
            SDL_Texture *back_texture_11,
            SDL_Texture *back_texture_15,
            SDL_Texture *back_texture_17, bool *tab, int Width, int Height) {
    bool onGround = false;
    for (int i = 0; i < FRAMES_COUNT; i++) {
        if (i == 0 || i == 4) {
            spriteRect->x += frameWidth;

            if (spriteRect->x >= textureWidth) {
                spriteRect->x = 0;
            }
        }

        switch (key) {
            case SDLK_a:
            case SDLK_LEFT: {
                if (spritePosition->x >
                    (int) (scale_x * (float) obj_arr[0].x1)) {
                    spritePosition->x -= STEPS_PER_FRAME;

                    if (side == SDLK_RIGHT) {
                        spriteRect->y -= frameHeight;
                    }
                    while (!checkOnBlocks(obj_arr, *spritePosition,
                                          countObjects, scale_y,
                                          scale_x).type) {
                        spritePosition->y += 1;
                        if (spritePosition->y % 10 == 0) {
                            renderStep(renderer, texture, *spriteRect,
                                       *spritePosition,
                                       backTexture, obj_arr, countObjects,
                                       scale_y, scale_x, back_texture_6,
                                       back_texture_11, back_texture_15,
                                       back_texture_17,*tab, Width, Height);
                        }
                        onGround = true;
                    }
                    side = SDLK_LEFT;
                }


                break;
            }
            case SDLK_d:
            case SDLK_RIGHT: {
                if (spritePosition->x + spritePosition->w <
                    (int) (scale_x * (float) obj_arr[0].x2)) {
                    spritePosition->x += STEPS_PER_FRAME;

                    if (side == SDLK_LEFT) {
                        spriteRect->y += frameHeight;
                    }
                    while (!checkOnBlocks(obj_arr, *spritePosition,
                                          countObjects, scale_y,
                                          scale_x).type) {
                        spritePosition->y += 1;
                        if (spritePosition->y % 10 == 0) {
                            renderStep(renderer, texture, *spriteRect,
                                       *spritePosition,
                                       backTexture, obj_arr, countObjects,
                                       scale_y, scale_x, back_texture_6,
                                       back_texture_11, back_texture_15,
                                       back_texture_17,*tab, Width, Height);
                        }
                        onGround = true;
                    }
                    side = SDLK_RIGHT;
                }

                break;
            }
            case SDLK_w:
            case SDLK_UP: {
                if (side == SDLK_RIGHT &&
                    spritePosition->x + spritePosition->w <
                    (int) (scale_x * (float) obj_arr[0].x2)) {
                    spritePosition->y -= STEPS_PER_FRAME * 13;
                    spritePosition->x += STEPS_PER_FRAME * 7;
                }
                if (side == SDLK_LEFT && spritePosition->x > (int) (scale_x *
                                                                    (float) obj_arr[0].x1)) {
                    spritePosition->y -= STEPS_PER_FRAME * 13;
                    spritePosition->x -= STEPS_PER_FRAME * 7;
                }

                break;
            }

            case SDLK_UNKNOWN: {
                while (!checkOnBlocks(obj_arr, *spritePosition,
                                      countObjects, scale_y, scale_x).type) {
                    spritePosition->y += 1;
                    if (spritePosition->y % 10 == 0) {
                        renderStep(renderer, texture, *spriteRect,
                                   *spritePosition,
                                   backTexture, obj_arr, countObjects, scale_y,
                                   scale_x, back_texture_6,
                                   back_texture_11, back_texture_15,
                                   back_texture_17,*tab, Width, Height);
                    }

                    onGround = true;
                }
//                spritePosition->y += STEPS_PER_FRAME * ;
                break;
            }
            default : {
                return;
            }

        }
        renderStep(renderer, texture, *spriteRect, *spritePosition,
                   backTexture, obj_arr, countObjects, scale_y, scale_x,
                   back_texture_6,
                   back_texture_11, back_texture_15,
                   back_texture_17,*tab, Width, Height);
    }

    if (key == SDLK_w || key == SDLK_UP) {
        renderSteps(renderer, texture, spriteRect, spritePosition, backTexture,
                    frameWidth, frameHeight, textureWidth, textureHeight,
                    SDLK_UNKNOWN, obj_arr, countObjects, scale_y, scale_x,
                    back_texture_6,
                    back_texture_11, back_texture_15,
                    back_texture_17,tab, Width, Height);
    }

    SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYMAPCHANGED);
}

int inputBox(SDL_Renderer *ren, SDL_Rect spritePosition, int Height,
             int countObjects, float scale_x, float scale_y, t_object *obj_arr,
             bool music_status) {
    char *in = (char *) malloc(sizeof(char) * 256);
    bool running = true;
    int len = 0;
    SDL_Color color = {255, 255, 255, 255};
    t_check_block check = checkOnBlocks(obj_arr, spritePosition,
                                        countObjects, scale_y, scale_x);
    if(check.index==11&&check.type==2&&!music_status){
        Mix_Chunk *engine_start = Mix_LoadWAV("../resource/1337.wav");
        Mix_PlayChannel(-1, engine_start, 0);
        SDL_Delay(3000);
    }
    SDL_StartTextInput();
        while (running) {
            SDL_Event ev;
            while (SDL_PollEvent(&ev)) {
                if (ev.type == SDL_TEXTINPUT) {
                    in[len] = ev.text.text[0];
                    len++;
                    in[len] = '\0';
                    insertText(ren, in, color,
                               (int) (scale_x * (float) obj_arr[0].x1),
                               Height - 40, 1);
                    //printf("%s",in);
                } else if (ev.type == SDL_KEYDOWN &&
                           ev.key.keysym.sym == SDLK_BACKSPACE && len != 0) {
                    len--;
                    in[len] = '\0';
                    insertText(ren, in, color,
                               (int) (scale_x * (float) obj_arr[0].x1),
                               Height - 40, 1);
                    //printf("%s",in);
                } else if (ev.type == SDL_KEYDOWN &&
                           ev.key.keysym.sym == SDLK_RETURN) {
                    running = false;
                }
            }
        }
        SDL_StopTextInput();
        insertText(ren, in, color, (int) (scale_x * (float) obj_arr[0].x1),
                   Height - 40, 1);
        SDL_RenderPresent(ren);

        if (check.type == 2) {
            switch (check.index) {
                case 6:
                    if (strcmp("14", in) == 0) {
                        obj_arr[check.index].type = 0;
                        return 1;
                    }
                    break;
                case 11:
                    if (strcmp("1337", in) == 0) {
                        obj_arr[check.index].type = 0;
                        return 1;
                    }
                    break;
                case 15:
                    if (strcmp("72105", in) == 0) {
                        obj_arr[check.index].type = 0;
                        return 1;
                    }
                    break;
                case 17:
                    if (strcmp("\\n", in) == 0) {
                        obj_arr[check.index].type = 0;
                        return 1;
                    }
                    break;
            }
        }
        //(int) (scale_x * (float) obj_arr[0].x1),Height-40,1);
    return 0;
}


int
closegame(SDL_Renderer *renderer, SDL_Texture *texture, SDL_Rect spriteRect,
          SDL_Rect spritePosition, SDL_Texture *backTexture, t_object *obj_arr,
          int countObjects, float scale_y, float scale_x,
          SDL_Texture *back_texture_6,
          SDL_Texture *back_texture_11,
          SDL_Texture *back_texture_15,
          SDL_Texture *back_texture_17, bool *music_status, int Width, int Height) {
    SDL_Event event;

    int textureWidth, textureHeight;
    int frameWidth, frameHeight;

    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);
    bool tab =false;
    frameWidth = textureWidth / 3;
    frameHeight = textureHeight / 2;
    int win = 4;
    while (1) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYUP:
                    if (event.key.keysym.sym==SDLK_TAB)
                            SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYMAPCHANGED);
                    tab=!(tab);
                    renderStep(renderer, texture, spriteRect,
                               spritePosition,
                               backTexture, obj_arr, countObjects,
                               scale_y, scale_x, back_texture_6,
                               back_texture_11, back_texture_15,
                               back_texture_17,tab, Width, Height);
                    SDL_FlushEvent(SDL_KEYDOWN);
                    SDL_FlushEvent(SDL_KEYUP);
                    break;
                case SDL_KEYDOWN: {
                    renderSteps(renderer, texture, &spriteRect,
                                &spritePosition, backTexture, frameWidth,
                                frameHeight, textureWidth, textureHeight,
                                event.key.keysym.sym, obj_arr, countObjects,
                                scale_y, scale_x, back_texture_6,
                                back_texture_11, back_texture_15,
                                back_texture_17,&tab,Width, Height);
                    SDL_FlushEvents(SDL_KEYDOWN, SDL_KEYMAPCHANGED);
                }

                    switch (event.key.keysym.sym) {
                        case SDLK_e:
                            win-=inputBox(renderer, spritePosition, frameHeight,
                                     countObjects, scale_x, scale_y, obj_arr,
                                     *music_status);
                            break;
                        case SDLK_m:

                            if (Mix_PausedMusic())
                                Mix_ResumeMusic();
                            else
                                Mix_PauseMusic();
                            *music_status = !(*music_status);
                            break;
                        case SDLK_ESCAPE:
                            return 1;
                    }
                    break;
                case SDL_QUIT:
                    return 1;
                default:
                    break;
            }
            if (win==0)
                return 0;
        }
    }

}
