### Entity Component System

## Table of Content
1. [Entities]
(#entities)
2. [Components]
(#components)

## Entities

- Entities are just IDs that are used to Track Components

## Components

- Components are "Data" that can be assigned to Entities, e.g. Velocity or Position

## Systems

- Systems do logic with Entities, e.g. MovementSystem or DamageSystem

## Entities Data

```c
#define MAX_ENTITIES 1000 //Define Max Entities
```
```c
typedef int Entity;  //Just an ID
```

## Entity API

Create entity, get ID returned
`createEntity();`

Destroy entity
`destroyEntity(Entity entity);`

Check if entity is alive, returns Boolean
`isEntityAlive(Entity entity);`

## Component Data

```c
struct {
float x, y;
}PositionComponent
```
```c
struct {
float vx, vy;
}VelocityComponent
```
```c
struct {
SDL_Texture* texture;
SDL_Rect srcRect
SDL_Rect dstRect
}TextureComponent
```

## Components API

Add position Component
`add_position_component(Entity entity, float x, float y)`

Add velocity Component
`add_velocity_coponent(Entity entity, float vx, float vy)

Add texture Component
`add_texture_component(Entity entity, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect);`
## System Data


## System API

Update Location depending on position and velocity Component, pass Refresh rate
`movementSystem(float deltaTime);`

Render every Entity if it has Texture
`render_texture(SDL_Renderer* renderer);

Load Texture from .bmp File
`loadTexture(SDL_Renderer* renderer, const char* file);`

