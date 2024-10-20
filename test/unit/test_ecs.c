#define SDL_MAIN_HANDLED
#include <assert.h>
#include <time.h>
#include <stdio.h>
#include "ecs/component.h"
#include "ecs/system.h"
#include "ecs/entity.h"
#include "logIt.h"
#include <SDL3/SDL.h>



// Unit test for ECS system
void test_add_and_get_position_component() {
	// Initialize components
	ECS_init_components();
    
	// Create an entity and add a position component
	ECS_Entity entity = 0; // Testing with the first entity
	ECS_add_position_component(entity, 10, 20);

	// Retrieve the position component
	ECS_PositionComponent* posComp = ECS_get_position_component(entity);

	// Assert that the position values are correct
	assert(posComp != NULL);
	assert(posComp->x == 10);
	assert(posComp->y == 20);

	unit_log("test_add_and_get_position_component passed!\n");

	// Cleanup
	ECS_free_components();
}

void test_add_and_get_velocity_component() {
	// Initialize components
	ECS_init_components();
	ECS_Entity entity = ECS_create_entity();
	// Create an entity and add a velocity component
ECS_add_velocity_component(entity, 5, 7); // Using integers

// Retrieve the velocity component
ECS_VelocityComponent* velComp = ECS_get_velocity_component(entity);

// Assert that the velocity values are correct
assert(velComp != NULL);
assert(velComp->vx == 5);
assert(velComp->vy == 7);

unit_log("test_add_and_get_velocity_component passed!\n");

// Cleanup
ECS_free_components();
ECS_destroy_entity(entity);
}

void test_entity_alive() {
	// Initialize the entity array
	//ECS_init_entities();

	// Create an entity
	ECS_Entity entity = ECS_create_entity();

	// Assert that the entity is alive
	assert(ECS_is_entity_alive(entity) == true);

	// Destroy the entity
	ECS_destroy_entity(entity);

	// Assert that the entity is no longer alive
	assert(ECS_is_entity_alive(entity) == false);

	unit_log("test_entity_alive passed!\n");
}

void test_movement_system() {
	// Initialize components
	ECS_init_components();
	ECS_Entity entity = ECS_create_entity();

	// Create an entity and add position and velocity components
	ECS_add_position_component(entity, 0, 0);  // Start at (0, 0)
	ECS_add_velocity_component(entity, 1, 1);  // Velocity (1, 1)

	// Simulate movement with a delta time of 1.0 (1 second)
	float deltaTime = 1.0f;
	ECS_movement_system(deltaTime);  // Assuming your movement system applies velocity

	// Retrieve the updated position component
	ECS_PositionComponent* posComp = ECS_get_position_component(entity);

	// Assert the new position after movement
	assert(posComp != NULL);
	assert(posComp->x == 1);  // Moved by 1 in the x-direction
	assert(posComp->y == 1);  // Moved by 1 in the y-direction

	unit_log("test_movement_system passed!\n");

	// Cleanup
	ECS_free_components();
	ECS_destroy_entity(entity);
}

void test_max_entities() {
    ECS_init_components();
    for (ECS_Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        ECS_Entity entity = ECS_create_entity();
        ECS_add_position_component(entity, entity, entity);
    }
    // Assert the last entity is alive and correctly initialized
    assert(ECS_is_entity_alive(MAX_ENTITIES - 1) == true);
    unit_log("test_max_entities passed! MAX:%d\n", MAX_ENTITIES);
}


int main (int argc, char* argv[])  {

struct timespec start, end;
initializeLogStreams();
test_add_and_get_position_component();
test_add_and_get_velocity_component();
test_entity_alive();
test_movement_system();
//Get starting time
timespec_get(&start, TIME_UTC);
test_max_entities();
//Get ending time
timespec_get(&end, TIME_UTC);
// Get time difference
long seconds = end.tv_sec - start.tv_sec;
long nanoseconds = end.tv_nsec - start.tv_nsec;
if (nanoseconds < 0) {
	seconds -= 1;
	nanoseconds += 100000000000;
	};
if (seconds > 0) {
	performance_log("test_max_entities(); Completed in :%ld.%09ld\n", seconds, nanoseconds);
	};
info_log("Test Passed");
return 0;
}
