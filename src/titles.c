#include "../inc/header.h"

void render_car(SDL_Renderer *ren, SDL_Texture *road, SDL_Texture *ucode,
                SDL_Texture *car, int x, int Width, int Height) {
    float scalex = (float) Width;
    scalex /= 1920;
    float scaley = (float) Height;
    scaley *= (float) 0.27777;
    scaley /= 300;
    SDL_Rect road_pos;
    road_pos.x = 0;
    road_pos.y = 40;
    road_pos.h = (int) ((float) 300 * scaley);
    road_pos.w = (int) ((float) 1920 * scalex);
    SDL_Rect road_src;
    road_src.x = (int)((float)x/scalex);
    road_src.y=0;
    road_src.w=1920;
    road_src.h=300;
    SDL_RenderCopy(ren,road,&road_src,&road_pos);
    SDL_Rect bus_pos;
    bus_pos.x = Width/10;
    bus_pos.y = 40 +(int) ((float) 150 * scaley);
    bus_pos.w =(int) ((float) 260* scalex);
    bus_pos.h = (int) ((float) 150 * scaley);
    SDL_RenderCopy(ren,car,NULL,&bus_pos);
    SDL_Rect ucode_pos;
    if (x > (int) ((float) 3840 * scalex)) {

    }
}

void titles(SDL_Renderer *ren, int Width, int Height) {
    SDL_FlushEvent(SDL_KEYDOWN);
    SDL_FlushEvent(SDL_KEYUP);
    SDL_RenderClear(ren);
    Mix_HaltMusic();
    Mix_Chunk *engine_start = Mix_LoadWAV("../resource/carstart.wav");
    Mix_Music *music = Mix_LoadMUS("../resource/central.mp3");
    SDL_Texture *road = IMG_LoadTexture(ren, "../resource/road_game.png");
    SDL_Texture *car = IMG_LoadTexture(ren,"../resource/bus.png");
    SDL_Texture *ucode = IMG_LoadTexture(ren,"../resource/unit_factory.png");
    render_car(ren,road,ucode,car,0,Width,Height);
    SDL_RenderPresent(ren);
    int start_engine = 0;
    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            if(start_engine<5) {
                                Mix_PlayChannel(-1, engine_start, 0);
                                start_engine++;
                                SDL_Delay(3000);
                            }
                            if (start_engine==5)
                                if(!Mix_PlayingMusic())
                                    Mix_PlayMusic(music, -1);
                            SDL_FlushEvent(SDL_KEYUP);

                    }
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_UP:
                        case SDLK_a:
                            break;
                        case SDLK_d:
                        case SDLK_DOWN:
                        case SDLK_s:
                            break;
                        case SDLK_q:
                            SDL_FlushEvent(SDL_KEYDOWN);
                            return;
                    }
                    break;

                case SDL_QUIT:
                    exit(0);
                default:
                    break;
            }
            SDL_FlushEvent(SDL_KEYDOWN);
            SDL_FlushEvent(SDL_KEYUP);
        }
    }
}
