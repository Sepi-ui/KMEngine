#define SDL_MAIN_HANDLED
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include "ecs/component.h"
#include "ecs/system.h"
#include "ecs/entity.h"
#include "logIt.h"
#include <SDL3/SDL.h>


void performanceTest_createEntity_and_AddComponents() {
ECS_Entity entity = 0;
ECS_create_entity();
ECS_init_components();
ECS_add_position_component(entity, 20, 20);
ECS_add_velocity_component(entity, 1, 1);
//Time duration of for loop
struct timespec start, end;
timespec_get(&start, TIME_UTC);
performance_log("calling ECS_movement_system 1000 times...\n");
for (int i = 0; i < 1000; i++) {
	ECS_movement_system(1.0f);
	};
timespec_get(&end, TIME_UTC);

// Get time difference
long seconds = end.tv_sec - start.tv_sec;
long nanoseconds = end.tv_nsec - start.tv_nsec;
if (nanoseconds < 0) {
	seconds -= 1;
	nanoseconds += 100000000000;
}
	performance_log("test_max_entities(); Completed in :%ld.%09ld\n", seconds, nanoseconds);

ECS_free_components();
}

int main (int argc, char* argv[]) {
initializeLogStreams();
performanceTest_createEntity_and_AddComponents();
}


