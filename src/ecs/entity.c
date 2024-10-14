#include "ecs/entity.h"

static bool entity_alive[MAX_ENTITIES] = {false};  // Track if an entity is alive or not

// Create a new entity (returns the first available entity ID)
ECS_Entity ECS_create_entity() {
    for (int i = 0; i < MAX_ENTITIES; i++) {
	//gets the next "dead" entity
        if (!entity_alive[i]) {
		// And makes it alive and returns ID
            entity_alive[i] = true;
            return i;  // Return the newly created entity ID
        }
    }
    return -1;  // No available entity slots
}

// Destroy an entity
void ECS_destroy_entity(ECS_Entity entity) {
    if (entity >= 0 && entity < MAX_ENTITIES) {
        entity_alive[entity] = false;
    }
}

// Check if an entity is alive
bool ECS_is_entity_alive(ECS_Entity entity) {
    return entity >= 0 && entity < MAX_ENTITIES && entity_alive[entity];
}

