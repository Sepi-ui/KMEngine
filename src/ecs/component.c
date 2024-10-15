#include <stdlib.h>
#include "ecs/component.h"
#include "ecs/entity.h"
#include "logIt.h"
#define MAX_ENTITIES 1000000
// Component arrays
ECS_PositionComponent* position_components;
ECS_VelocityComponent* velocity_components;


//array for Texture data, array for "hasTexture"
ECS_TextureComponent* textures;
static bool has_texture[MAX_ENTITIES] = {false};

void ECS_init_components() {
position_components = malloc(MAX_ENTITIES * sizeof(ECS_PositionComponent));
if (position_components == NULL) {
	fatal_log("Could not allocate Memory for position_components");
	};

velocity_components = malloc(MAX_ENTITIES * sizeof(ECS_VelocityComponent));
if (velocity_components == NULL) {
	fatal_log("Could not allocate Memory for velocity_components");
	};
textures = malloc(MAX_ENTITIES * sizeof(ECS_TextureComponent));
if (textures == NULL) {
	fatal_log("Could not allocate Memory for textures");
	};
};


void ECS_free_components() {
free(position_components);
free(velocity_components);
free(textures);
};


// Add position component to an entity
void ECS_add_position_component(ECS_Entity entity, float x, float y) {
    position_components[entity].x = x;
    position_components[entity].y = y;
}

ECS_PositionComponent* ECS_get_position_component() {
return position_components;
}

// Add velocity component to an entity
void ECS_add_velocity_component(ECS_Entity entity, float vx, float vy) {
    velocity_components[entity].vx = vx;
    velocity_components[entity].vy = vy;
}

ECS_VelocityComponent* ECS_get_velocity_component() {
return velocity_components;
}

void ECS_add_texture_component(ECS_Entity entity, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect) {
	textures[entity].texture = texture;
	textures[entity].srcRect = srcRect;
	textures[entity].dstRect = dstRect;
	has_texture[entity] = true;
}

ECS_TextureComponent* ECS_get_texture_component(ECS_Entity entity) {
    if (has_texture[entity]) {
        return &textures[entity];
    }
    return NULL;
}
