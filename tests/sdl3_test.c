
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "../include/ecs/entity.h"
#include "../include/ecs/component.h"
#include "../include/ecs/system.h"


int main (int argc, char* argv[]) {



	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (result < 0) {
	SDL_Log("SDL_Init errr %s", SDL_GetError());
	return -1;
	};

	window = SDL_CreateWindow("SDL3 My first Window", 800, 600, 0);
	if (window = NULL) {
	SDL_Log("SDL_CreateWindow error %s", SDL_GetError());
	return -2;
	};


	//Create entity
	Entity badge = createEntity();



	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
	SDL_Log("SDL_CreateRenderer error %s", SDL_GetError());
	return -2;
	};
	SDL_Log("SDL3 initialized");


	SDL_Texture* badgeTexture = load_texture(renderer, "../../../badge.bmp");

	// Define source and destination rectangles (for positioning and sprite rendering)
	SDL_Rect srcRect = {0, 0, 32, 32};  // Entire image or portion of sprite sheet
	SDL_Rect dstRect = {100, 100, 64, 64};  // On-screen position and size

	add_texture_component(badge, badgeTexture, srcRect, dstRect);

	SDL_Event event;

	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_EVENT_QUIT:
			SDL_Log ("SDL* Event quit");
			quit = 1;
			break;
			};
		};

	SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 0xff);
	SDL_RenderClear(renderer);

	//Draw here
	render_system(renderer);


	
	SDL_RenderPresent(renderer);
	SDL_Delay(1000);

	};

	SDL_Log("SDL3 shutdown");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
return 0;
};

