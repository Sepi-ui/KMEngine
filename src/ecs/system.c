#include <stdio.h>

#include "system.h"
#include "entity.h"
#include "component.h"
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
	for (int i = 0; i < MAX_ENTITIES; i++) {
	TextureComponent* textureComp = get_texture_component(i);
	if (textureComp) {
		SDL_RenderTexture(renderer, textureComp->texture, &textureComp->srcRect, &textureComp->dstRect);
		};
	
	};
}

SDL_Texture* load_texture(SDL_Renderer* renderer, const char* file) {

	//Load file into Memory
	size_t filesize;
	void* fileData = SDL_LoadFile(file, &filesize);
	if (!fileData) {
        	printf("Could not load file: %s\n", SDL_GetError());
        	return NULL;
    	}

	//Create a surface from the file data
	SDL_Surface* surface = SDL_CreateSurface(fileData, filesize);

	if (!surface) {
	fatal_log("Could not Load File");
	SDL_free(fileData);
	return NULL;
	};

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (!texture) {
	fatal_log("Could not load File into memory");
	SDL_DestroySurface(surface);
	SDL_free(fileData);
	return NULL;
	};

	SDL_DestroySurface(surface);
	SDL_free(fileData);
    return texture;
}

