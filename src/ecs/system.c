#include <stdio.h>

#include "ecs/system.h"
#include "ecs/entity.h"
#include "ecs/component.h"
#include "logIt.h"

#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <png.h>

// Movement system: updates entities' positions based on their velocity
void movement_system(float deltaTime) {
    for (Entity entity = 0; entity < MAX_ENTITIES; entity++) {
        if (isEntityAlive(entity)) {
            // Update only if the entity has both position and velocity components
            position_components[entity].x += velocity_components[entity].vx * deltaTime;
            position_components[entity].y += velocity_components[entity].vy * deltaTime;
        }
    }
}

//Rendering System

void render_system(SDL_Renderer* renderer) {
	SDL_Rect currentViewport;
	SDL_GetRenderViewport(renderer, &currentViewport);
	for (int i = 0; i < MAX_ENTITIES; i++) {
	TextureComponent* textureComp = get_texture_component(i);
	PositionComponent* posComp = get_position_component(i);
	if (textureComp && posComp) {
		//Convert int Data to floating Point for Rendering
	
		SDL_FRect srcFRect = {
	
		(float)textureComp->srcRect.x,
		(float)textureComp->srcRect.y,
		(float)textureComp->srcRect.w,
		(float)textureComp->srcRect.h,
		};

		SDL_FRect dstFRect;
		dstFRect = (SDL_FRect){
		(float)posComp->x - currentViewport.x,
		(float)posComp->y - currentViewport.y,
		textureComp->dstRect.w,
		textureComp->dstRect.h,
		};
	//printf("Entity %d position: (%f, %f)\n", i, posComp->x, posComp->y);

	
		SDL_RenderTexture(renderer, textureComp->texture, &srcFRect, &dstFRect);
		};
	
	};
}

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file) {

	SDL_Surface* surface = SDL_LoadBMP(file);
	if (!surface) {
	printf("Error loading BMP\n");
	return NULL; 
	};

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (!texture) {
	printf("Error loading Texture from surface");
	SDL_DestroySurface(surface);
	return NULL;
	};

	SDL_DestroySurface(surface);
    return texture;
}

