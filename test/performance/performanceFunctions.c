#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL3/SDL.h>

#ifdef _WIN32
	#include <windows.h>
	#include <psapi.h>
#endif
#include "../../include/windowHandling.h"
#include "ecs/component.h"
#include "ecs/system.h"
#include "ecs/component.h"
#include "../../include/performanceFunctions.h"
#include "logIt.h"
#define MAX_ENTITIES 100000


typedef struct LogLayout {
	int index;
	float frameTime;
	float memoryUsage;
	float cpuUsage;
}LogLayout;
float PERF_get_memory_usage() {
// Windows memory usage
#ifdef _WIN32
    PROCESS_MEMORY_COUNTERS memCounters;
    HANDLE process = GetCurrentProcess(); // Get the handle to the current process

    if (GetProcessMemoryInfo(process, &memCounters, sizeof(memCounters))) {
        SIZE_T memoryUsageBytes = memCounters.WorkingSetSize; // Memory usage in bytes
	//Convert to float
	float memoryUsageMB = (float)memoryUsageBytes / (1024 * 1024);
	return memoryUsageMB;
    } else {
        error_log("Could not retrieve memory information.\n");
	return -1.0f;
    }
//Linux memory usage
#elif __linux__
FILE* file = fopen("/proc/self/status", "r");
if (file == NULL) {
	error_log("could not open /proc/self/status");
	return -1.0f;
	};
size_t memoryUsageKB = 0;
char buffer[256];

while (fgets(buffer, sizeof(buffer), file)) {
	if (scanf(buffer, "VmRSS: %zu kB", &memoryUsageKB) == 1) {
		break;
		};
	};
	fclose(file);

	float memoryUsageMB = (float)memoryUsageKB / 1024;
	return memoryUsageMB;

#else
error_log("unsupported platform.\n");
return -1.0f;
#endif


}

void PERF_rendering_test(int load, int iteration) {
	srand(time(NULL));
	//declare buffer to write to
	LogBuffer* buffer = initialize_log_buffer(1024);
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
	ECS_init_components();
	while (i < load && i < MAX_ENTITIES) {
	ECS_Entity entity = ECS_create_entity();

	//Get window Size
	int windowWidth, windowHeight;
	SDL_GetWindowSize(window, &windowWidth, &windowHeight);
 // Randomize position and velocity components

	int posX = rand() % windowWidth;  // Random x position between 0 and 800 (window width)
	int posY = rand() % windowHeight;  // Random y position between 0 and 600 (window height)
	int velX = (rand() % 10) - 5;  // Random velocity between -5 and 4
	int velY = (rand() % 10) - 5;  // Random velocity between -5 and 4
	printf("posX = %d, posY = %d", posX, posY);
	ECS_add_position_component(entity, posX, posY);
	ECS_add_velocity_component(entity, velX, velY);

	SDL_Rect srcRect = {0, 0, 32, 32};  // Entire image or portion of sprite sheet
	SDL_Rect dstRect = {posX, posY, 64, 64};  // Position, last 2 define expansion
	SDL_Texture* entityTexture = ECS_load_texture(renderer, "test/assets/badge.bmp");
	if (entityTexture == NULL) {
		error_log("Texture loading of badge.bmp");
		exit(EXIT_FAILURE);
		};
	ECS_add_texture_component(entity, entityTexture, srcRect, dstRect);
	i++;
	};
	list_entities();
	SDL_Event event;
	//Rendering loop
	struct timespec start, end;
	double elapsedTime = 0.0;
	double totalFrameTime = 0.0;
	int j = 0;
	int quit = 0;
	buffer_log(buffer, "Iteration | FrameTime | MemoryUsage\n");
		while (!quit && j < iteration && j < MAX_ENTITIES) {
			while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
				quit = 1;  // Exit loop if user closes the window
				break;

				case SDL_EVENT_WINDOW_RESIZED:
				handleWindowResize(window, renderer);
				break;
			}
			}
		//Update viewport
		int windowWidth, windowHeight; 
		SDL_GetWindowSize(window, &windowWidth, &windowHeight);
		SDL_Rect viewport = { 0, 0, windowWidth, windowHeight };
		SDL_SetRenderViewport(renderer, &viewport);

		clock_gettime(CLOCK_MONOTONIC, &start);
		PERF_get_memory_usage();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		ECS_movement_system(0.016);
		ECS_render_system(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(10);

		clock_gettime(CLOCK_MONOTONIC, &end);
		// Calculate elapsed time for the frame
		double frameTime = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
		elapsedTime += frameTime;

		totalFrameTime += frameTime;
		float memUsage = PERF_get_memory_usage();
		buffer_log(buffer, "Index: %d\t%f\t%f\n", j + 1, frameTime, memUsage);
		j++;
		};

double avgFrameTime = totalFrameTime / iteration;
double avgFps = 1.0 / avgFrameTime;
performance_log("Average Frame Time: %f seconds\n", avgFrameTime);
performance_log("Average FPS: %f\n", avgFps);

//Cleanup
for (ECS_Entity i = 0; i < load && i < MAX_ENTITIES; i++) {
	ECS_destroy_entity(i);
	};
	info_log("cleaned up entities\n");

SDL_DestroyRenderer(renderer);
SDL_DestroyWindow(window);
SDL_Quit();
write_buffer_to_file(buffer, "test/performance/performanceLog.txt");

return;
}

void PERF_collision_test(int load, int iteration) {

return;
}

void PERF_physics_test(int load, int iteration) {
return;
}
