#ifndef COMPONENT_H
#define COMPONENT_H
#include <SDL3/SDL.h>
#include "entity.h"


//Position component
typedef struct {
	float x, y;
}ECS_PositionComponent;

//Velocity Component
typedef struct {
	float vx, vy;
}ECS_VelocityComponent;

//Texture component
typedef struct {
	SDL_Texture* texture;
	SDL_Rect srcRect;
	SDL_Rect dstRect;
}ECS_TextureComponent;


void ECS_init_components();
void ECS_free_components();
void ECS_add_position_component(ECS_Entity entity, float x, float y);
ECS_PositionComponent* ECS_get_position_component();
void ECS_add_velocity_component(ECS_Entity entity, float vx, float vy);
ECS_VelocityComponent* ECS_get_velocity_component();

void ECS_add_texture_component(ECS_Entity entity, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect);
ECS_TextureComponent* ECS_get_texture_component(ECS_Entity entity);
#endif // COMPONENT_H
