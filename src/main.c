#include "../inc/header.h"

bool insertText(SDL_Renderer *gRenderer, char *textureText, SDL_Color
textColor, int x, int y, int flag) {
    TTF_Init();
    TTF_Font *gFont;
    if (flag == 0) {
        gFont = TTF_OpenFont("../resource/tcfont.ttf", 26);
    } else {
        gFont = TTF_OpenFont("../resource/tcfont.ttf", 38);
    }
    if (!gFont) {
        printf("Failed to render text texture!\n");
    }
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

void drawer(SDL_Renderer *ren, int Width, int Height, int counter) {
    SDL_Color textColor1 = {255, 255, 176};
    SDL_Color textColor2 = {200, 150, 0};
    SDL_Color backColor = {35, 147, 255, 49};
    //insertText(ren, "Tidy coder", textColorlogo, Width / 3+20, Height / 6,0);

    SDL_Surface *background = SDL_LoadBMP("../resource/menu_back.bmp");
    SDL_Texture *texture = SDL_CreateTextureFromSurface(ren, background);
    SDL_RenderCopy(ren, texture, NULL, NULL);
    SDL_Rect menu_back;
    menu_back.x = Width / 14 * 5;
    menu_back.y = Height / 12 * 5;
    menu_back.w = Width - Width / 14 * 10;
    menu_back.h = Height - (int) ((float) Height / 12 * 7.5);
    SDL_SetRenderDrawColor(ren, backColor.r, backColor.g, backColor.b,
                           backColor.a);
    SDL_RenderFillRect(ren, &menu_back);
    SDL_RenderDrawRect(ren, &menu_back);
    if (counter == 0) {
        insertText(ren, "New game", textColor1, Width / 7 * 3, Height / 2, 1);
        insertText(ren, "Turn off the music", textColor2, Width / 7 * 3,
                   Height / 2 + 100, 1);
        insertText(ren, "Exit", textColor2, Width / 7 * 3, Height / 2 + 200,
                   1);
    }
    if (counter == 1) {
        insertText(ren, "New game", textColor2, Width / 7 * 3, Height / 2, 1);
        insertText(ren, "Turn off the music", textColor1, Width / 7 * 3,
                   Height / 2 + 100, 1);
        insertText(ren, "Exit", textColor2, Width / 7 * 3, Height / 2 + 200,
                   1);
    }
    if (counter == 2) {
        insertText(ren, "New game", textColor2, Width / 7 * 3, Height / 2, 1);
        insertText(ren, "Turn off the music", textColor2, Width / 7 * 3,
                   Height / 2 + 100, 1);
        insertText(ren, "Exit", textColor1, Width / 7 * 3, Height / 2 + 200,
                   1);
    }
    insertText(ren, "To play use ENGLISH(qwerty) keymap", textColor1, 10,
               Height - 50,
               1);
    SDL_Color textColorsystem = {255, 255, 255};
    insertText(ren,
               "Use WASD and arrows for moving",
               textColorsystem, 0, 0, 0);

    insertText(ren,
               "Use E to interact",
               textColorsystem, 0, 42, 0);

    insertText(ren,
               "Use TAB to call StackOwerflow",
               textColorsystem, 0, 84, 0);
    insertText(ren,
               "Use M to turn off the music",
               textColorsystem, 0, 126, 0);

    insertText(ren,
               "Use ESC or Q to exit",
               textColorsystem, 0, 168, 0);
    SDL_RenderPresent(ren);

}

void chooser(int counter, Mix_Music *bgm, SDL_Renderer *ren, int Width,
             int Height, bool *music_status) {
    if (counter == 0) {
        printf("starting the game\n");
        if (level0(ren, Width, Height, music_status) == 0)
            titles(ren, Width, Height);
        drawer(ren, Width, Height, 0);
        Mix_HaltMusic();
        Mix_PlayMusic(bgm, -1);
    }
    if (counter == 1) {
        if (Mix_PausedMusic())
            Mix_ResumeMusic();
        else
            Mix_PauseMusic();
        *music_status = !*music_status;
    }
    if (counter == 2) {
        SDL_Quit();
        exit(0);
    }
}


int main() {
    /*
     *
     * Starting window
     *
     * SDL_DisplayMode DM
     *
     * SDL_Window *win //SDL_WINDOW_FULLSCREEN_DESKTOP
     *
     * SDL_Renderer *ren //SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC
     *
     * SDL_Surface *screen //RGBA fullscreen surface
     *
     * */

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL_Init Error: %s", SDL_GetError());
        return 1;
    }
    Mix_Init(MIX_INIT_MP3);
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    int Width = DM.w;       //width of screen
    int Height = DM.h;      //height of screen
    SDL_Window *win = SDL_CreateWindow("Tidy Coder", 0, 0, Width, Height,
                                       SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (win == NULL) {
        printf("SDL_CreateWindow Error: %s", SDL_GetError());
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        printf("SDL_CreateRenderer Error: %s", SDL_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
               Mix_GetError());
    }


    SDL_Surface *screen = SDL_CreateRGBSurface(0, Width, Height, 32, 0, 0, 0,
                                               0);
    if (screen == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }
    int poscounter = 0;
    Mix_Music *bgm = Mix_LoadMUS("../resource/bgm.mp3");
    if (!Mix_PlayingMusic())
        Mix_PlayMusic(bgm, -1);
    SDL_SetRenderDrawColor(ren, 0, 0, 105, 255);
    SDL_RenderClear(ren);
    bool done = false;
    SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
    drawer(ren, Width, Height, poscounter);
    bool music_status = true;
   // *music_status = true;
    SDL_Event event;
    while (1) {
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                        case SDLK_UP:
                        case SDLK_a:
                            if (poscounter == 0)
                                poscounter = 2;
                            else poscounter--;
                            drawer(ren, Width, Height, poscounter);
                            usleep(10000);
                            break;
                        case SDLK_d:
                        case SDLK_DOWN:
                        case SDLK_s:
                            if (poscounter == 2)
                                poscounter = 0;
                            else poscounter++;
                            drawer(ren, Width, Height, poscounter);
                            usleep(10000);
                            break;
                        case SDLK_RETURN:
                            chooser(poscounter, bgm, ren, Width, Height,
                                    &music_status);
                            break;
                        case SDLK_ESCAPE:
                            return 0;
                    }
                    break;

                case SDL_QUIT:
                    Mix_Quit();
                    return 0;
                default:
                    break;
            }
            SDL_FlushEvent(SDL_KEYDOWN);
        }
    }


    return 0;
}
