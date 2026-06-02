#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#define SCREEN_W 800
#define SCREEN_H 480
#define FONT_SIZE 48
#define SPLASH_DURATION_MS 3000

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init error: %s\n", TTF_GetError());
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0) {
        fprintf(stderr, "IMG_Init error: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
        "sct-app",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_W, SCREEN_H,
        SDL_WINDOW_FULLSCREEN
    );
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);

    SDL_Surface *splash_surf = IMG_Load("/usr/share/sct-app/splash.png");
    if (!splash_surf) {
        fprintf(stderr, "Failed to load splash: %s\n", IMG_GetError());
        //
    } else {
        SDL_Texture *splash_tex = SDL_CreateTextureFromSurface(ren, splash_surf);
        SDL_FreeSurface(splash_surf);

        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, splash_tex, NULL, NULL);
        SDL_RenderPresent(ren);

        SDL_Delay(SPLASH_DURATION_MS);

        SDL_DestroyTexture(splash_tex);
    }

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/dejavu/DejaVuSans.ttf", FONT_SIZE);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont error: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, "Hello, World!", white);
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);

    SDL_Rect dst = {
        (SCREEN_W - surf->w) / 2,
        (SCREEN_H - surf->h) / 2,
        surf->w, surf->h
    };

    SDL_FreeSurface(surf);
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_RenderPresent(ren);

    SDL_Event e;
    while (1) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) goto done;
        }
        SDL_Delay(100);
    }

done:
    SDL_DestroyTexture(tex);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}