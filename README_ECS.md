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

## Component API

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

