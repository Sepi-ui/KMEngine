#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef _WIN32
	#include <windows.h>
	#include <psapi.h>
#endif
#include "ecs/component.h"
#include "ecs/system.h"
#include "ecs/component.h"
#include "../../include/performanceFunctions.h"
#include "logIt.h"
#define MAX_ENTITIES 100000

void log_memory_usage() {
// Windows memory usage
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memCounters;
    HANDLE process = GetCurrentProcess(); // Get the handle to the current process

    if (GetProcessMemoryInfo(process, &memCounters, sizeof(memCounters))) {
        SIZE_T memoryUsage = memCounters.WorkingSetSize; // Memory usage in bytes
        info_log("Current Memory Usage: %zu KB\n", memoryUsage / 1024);
    } else {
        error_log("Could not retrieve memory information.\n");
    }
#elif __linux__


#endif


}

void rendering_performance_test(int load, int iteration) {
	info_log("running rendering test...");
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);
	if (result < 0) {
	SDL_Log("SDL_Init errr %s", SDL_GetError());
	return;
	};

	window = SDL_CreateWindow("SDL3 My first Window", 800, 600, SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
	SDL_Log("SDL_CreateWindow error %s", SDL_GetError());
	return;
	};



	renderer = SDL_CreateRenderer(window, NULL);
	if (renderer == NULL) {
	SDL_Log("SDL_CreateRenderer error %s", SDL_GetError());
	return;
	};
	SDL_Log("SDL3 initialized\n");
	srand(time(NULL));
	//Initialize Entities
	int i = 0;
	while (i < load && i < MAX_ENTITIES) {
	ECS_Entity entity;
	entity = ECS_create_entity();
	ECS_init_components();
 // Randomize position and velocity components
	int posX = rand() % 600;  // Random x position between 0 and 800 (window width)
	int posY = rand() % 400;  // Random y position between 0 and 600 (window height)
	int velX = (rand() % 10) - 5;  // Random velocity between -5 and 4
	int velY = (rand() % 10) - 5;  // Random velocity between -5 and 4
	ECS_add_position_component(entity, posX, posY);
	ECS_add_velocity_component(entity, velX, velY);

	SDL_Rect srcRect = {0, 0, 32, 32};  // Entire image or portion of sprite sheet
	SDL_Rect dstRect = {0, 0, 64, 64};  // Position, last 2 define expansion
	SDL_Texture* entityTexture = ECS_load_texture(renderer, "test/assets/badge.bmp");
	ECS_add_texture_component(entity, entityTexture, srcRect, dstRect);
	i++;
	};

	SDL_Event event;
	//Rendering loop
	struct timespec start, end;
	double elapsedTime = 0.0;
	double totalFrameTime = 0.0;
	int j = 0;
	int quit = 0;
while (!quit) {
	while (j < iteration && j < MAX_ENTITIES) {
		if (event.type == SDL_EVENT_QUIT) {
		quit = 1;  // Exit loop if user closes the window
		};
        
	clock_gettime(CLOCK_MONOTONIC, &start);
	log_memory_usage();
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	ECS_movement_system(1.0f);
	ECS_render_system(renderer);

	SDL_RenderPresent(renderer);


	clock_gettime(CLOCK_MONOTONIC, &end);
	// Calculate elapsed time for the frame
	double frameTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
	elapsedTime += frameTime;

	totalFrameTime += frameTime;
	info_log("Iteration %d: Frame Time = %f seconds\n", j + 1, frameTime);
	j++;
	};
double avgFrameTime = totalFrameTime / iteration;
double avgFps = 1.0 / avgFrameTime;
info_log("Average Frame Time: %f seconds\n", avgFrameTime);
info_log("Average FPS: %f\n", avgFps);

//Cleanup
for (ECS_Entity i = 0; i < load && i < MAX_ENTITIES; i++) {
	ECS_destroy_entity(i);
	};
	info_log("cleaned up entities\n");

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
quit = 1;
};
return;
}

void collision_performance_test(int load, int iteration) {
return;
}

void physics_performance_test(int load, int iteration) {
return;
}
