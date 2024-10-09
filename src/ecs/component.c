#include "ecs/component.h"
#include "ecs/entity.h"
// Component arrays (statically sized for all possible entities)
PositionComponent position_components[MAX_ENTITIES];
VelocityComponent velocity_components[MAX_ENTITIES];

//array for Texture data, array for "hasTexture"
static TextureComponent textures[MAX_ENTITIES];
static bool has_texture[MAX_ENTITIES] = {false};


// Add position component to an entity
void add_position_component(Entity entity, float x, float y) {
    position_components[entity].x = x;
    position_components[entity].y = y;
}

// Add velocity component to an entity
void add_velocity_component(Entity entity, float vx, float vy) {
    velocity_components[entity].vx = vx;
    velocity_components[entity].vy = vy;
}

void add_texture_component(Entity entity, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect) {
	textures[entity].texture = texture;
	textures[entity].srcRect = srcRect;
	textures[entity].dstRect = dstRect;
	has_texture[entity] = true;
}

TextureComponent* get_texture_component(Entity entity) {
    if (has_texture[entity]) {
        return &textures[entity];
    }
    return NULL;
}
