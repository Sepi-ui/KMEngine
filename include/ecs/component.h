#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL3/SDL.h>
#include "entity.h"
#define MAX_ENTITIES 1000


//Position component
typedef struct {
	float x, y;
}PositionComponent;

//Velocity Component
typedef struct {
	float vx, vy;
}VelocityComponent;

//Texture component
typedef struct {
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
}TextureComponent;

// Arrays to hold components for each entity
extern PositionComponent position_components[MAX_ENTITIES];
extern VelocityComponent velocity_components[MAX_ENTITIES];

void add_position_component(Entity entity, float x, float y);
void add_velocity_component(Entity entity, float vx, float vy);

void add_texture_component(Entity entity, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect);
TextureComponent* get_texture_component(Entity entity);
#endif // COMPONENT_H
