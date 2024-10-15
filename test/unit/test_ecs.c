#define SDL_MAIN_HANDLED
#include <assert.h>
#include <stdio.h>
#include "ecs/component.h"
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

	printf("test_add_and_get_position_component passed!\n");

	// Cleanup
	ECS_free_components();
}


int main (int argc, char* argv[])  {
test_add_and_get_position_component();
info_log("Test Passed");
return 0;
}
