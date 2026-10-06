#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

#define SCREEN_W 800
#define SCREEN_H 480
#define FONT_SIZE 48

int main(void) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL_Init error: %s\n", SDL_GetError());
        return 1;
    }

    if (TTF_Init() < 0) {
        fprintf(stderr, "TTF_Init error: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Window *win = SDL_CreateWindow(
        "sct-app",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_W, SCREEN_H,
        SDL_WINDOW_FULLSCREEN
    );
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow error: %s\n", SDL_GetError());
        goto cleanup;
    }

    // Software renderer works well on the Car Thing
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer error: %s\n", SDL_GetError());
        goto cleanup;
    }

    TTF_Font *font = TTF_OpenFont("/usr/share/fonts/dejavu/DejaVuSans.ttf", FONT_SIZE);
    if (!font) {
        fprintf(stderr, "TTF_OpenFont error: %s\n", TTF_GetError());
        goto cleanup;
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *surf = TTF_RenderUTF8_Blended(font, "Hello, World!", white);
    if (!surf) {
        fprintf(stderr, "TTF_RenderUTF8_Blended error: %s\n", TTF_GetError());
        goto cleanup;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, surf);
    SDL_Rect dst = {
        (SCREEN_W - surf->w) / 2,
        (SCREEN_H - surf->h) / 2,
        surf->w, surf->h
    };

    SDL_FreeSurface(surf);

    // Clear screen to black, draw text, and present
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, &dst);
    SDL_RenderPresent(ren);

    // Event loop to keep the app running until closed
    SDL_Event e;
    while (1) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) goto done;
        }
        SDL_Delay(100);
    }

done:
    if (tex) SDL_DestroyTexture(tex);
    if (font) TTF_CloseFont(font);
cleanup:
    if (ren) SDL_DestroyRenderer(ren);
    if (win) SDL_DestroyWindow(win);
    TTF_Quit();
    SDL_Quit();
    return 0;
}