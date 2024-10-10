#include <stdio.h>
#include <SDL3/SDL.h>


void handleWindowResize(SDL_Window* window, SDL_Renderer* renderer) {
int newWidth, newHeight;

SDL_GetWindowSize(window, &newWidth, &newHeight);

SDL_Rect viewport = {0, 0, newWidth, newHeight};
SDL_SetRenderViewport(renderer, &viewport);
}
