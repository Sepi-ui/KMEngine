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
//trace_log("entity created");
ECS_create_entity();
ECS_init_components();
ECS_add_position_component(entity, 20, 20);
ECS_add_velocity_component(entity, 1, 1);

for (int i = 0; i < 1000; i++) {
	ECS_movement_system(1.0f);
	};
ECS_free_components();
}

int main (int argc, char* argv[]) {
//info_log("started main");
performanceTest_createEntity_and_AddComponents();
}


