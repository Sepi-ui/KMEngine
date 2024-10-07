#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL3/SDL.h>
#include "entity.h"
#include "component.h"

// Movement system: updates the position of entities with both position and velocity components
void movement_system(float deltaTime);

//Rendering System
void render_system(SDL_Renderer* renderer);

// Load Textures
SDL_Texture* load_texture(SDL_Renderer*, const char* file);

#endif // SYSTEM_H

