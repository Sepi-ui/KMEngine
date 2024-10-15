### Entity Component System

## Table of Content

1. [Entity](#entity)
2. [Component](#components)
3. [System](#system)

### Data structures

1. [Entity Data](#entity-data)
2. [Component Data](#component-data)
3. [System Data](#system-data)

### API's

1. [Entity API](#entity-api)
2. [Component API](#component-api)
3. [System API](#system-api)

## Entity

- Entities are just IDs that are used to Track Components

## Component

- Components are "Data" that can be assigned to Entities, e.g. Velocity or Position

## System

- Systems do logic with Entities, e.g. MovementSystem or DamageSystem

## Entity Data

```c
#define MAX_ENTITIES 1000 //Define Max Entities
```
```c
typedef int ECS_Entity;  //Just an ID
```

## Entity API

Create entity, get ID returned

`ECS_create_entity();`

Destroy entity

`ECS_destroy_entity(ECS_Entity entity);`

Check if entity is alive, returns Boolean
`ECS_is_entity_alive(ECS_Entity entity);`

## Component Data

```c
struct {
float x, y;
}ECS_PositionComponent
```
```c
struct {
float vx, vy;
}ECS_VelocityComponent
```
```c
struct {
SDL_Texture* texture;
SDL_Rect srcRect
SDL_Rect dstRect
}ECS_TextureComponent
```

## Component API

Add position Component
`ECS_add_position_component(ECS_Entity entity, float x, float y)`

Add velocity Component
`ECS_add_velocity_coponent(ECS_Entity entity, float vx, float vy)`

Add texture Component
`ECS_add_texture_component(Entity entity, SDL_Texture* texture, SDL_Rect srcRect, SDL_Rect dstRect);`
## System Data


## System API

Update Location depending on position and velocity Component, pass Refresh rate
`movementSystem(float deltaTime);`

Render every Entity with Texture
`ECS_render_texture(SDL_Renderer* renderer);`

Load Texture from .bmp File
`ECS_load_texture(SDL_Renderer* renderer, const char* file);`

