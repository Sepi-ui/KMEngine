
#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>
#include <png.h>
#include "../include/ecs/entity.h"
#include "../include/ecs/component.h"
#include "../include/ecs/system.h"
#include "../include/windowHandling.h"
#include "../include/logit.h"


int main (int argc, char* argv[]) {



	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (result < 0) {
	SDL_Log("SDL_Init errr %s", SDL_GetError());
	return -1;
	};

	window = SDL_CreateWindow("SDL3 My first Window", 800, 600, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
	SDL_Log("SDL_CreateWindow error %s", SDL_GetError());
	return -2;
	};



	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
	SDL_Log("SDL_CreateRenderer error %s", SDL_GetError());
	return -2;
	};
	SDL_Log("SDL3 initialized");


	// Define source and destination rectangles (for positioning and sprite rendering)
	ECS_init_components();
	//Create entity
	ECS_Entity badge = ECS_create_entity();
	trace_log("created Entity");
	ECS_add_position_component(badge, 40, 40);
	trace_log("added Position Component");
	ECS_add_velocity_component(badge, 100, 100);
	trace_log("added Velocity Component");
	SDL_Rect srcRect = {0, 0, 32, 32};  // Entire image or portion of sprite sheet
	SDL_Rect dstRect = {0, 0, 64, 64};  // Position, last 2 define expansion
	//Load texture and add to Entity
	SDL_Texture* badgeTexture = ECS_load_texture(renderer, "tests/assets/badge.bmp");
	ECS_add_texture_component(badge, badgeTexture, srcRect, dstRect);
	trace_log("Created and loaded Entity");


	SDL_Event event;

	int quit = 0;
	while (!quit) {
		while (SDL_PollEvent(&event)) {
		switch (event.type) {

			case SDL_EVENT_QUIT:
				SDL_Log ("SDL* Event quit");
				quit = 1;
				break;

			case SDL_EVENT_KEY_DOWN:
			if(event.key.key == SDLK_ESCAPE) {
				quit = 1;
				};
			if(event.key.key == SDLK_F11) {
				Uint32 fullscreenFlag = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
				if (fullscreenFlag) {
            				// Switch to windowed mode
            				SDL_SetWindowFullscreen(window, false);
        			}else{
            				// Switch to borderless fullscreen
            				SDL_SetWindowFullscreen(window, true);
        				};
				};
				break;

	 		case SDL_EVENT_WINDOW_RESIZED:
				handleWindowResize( window, renderer);
				break;
			};
		};

	SDL_SetRenderDrawColor(renderer, 0, 0, 0xff, 0xff);
	SDL_RenderClear(renderer);

	ECS_movement_system(0.016);
	//Draw here
	ECS_render_system(renderer);

	
	SDL_RenderPresent(renderer);
	SDL_Delay(16);

	};

	SDL_Log("SDL3 shutdown");
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	ECS_destroy_entity(badge);
return 0;
};

