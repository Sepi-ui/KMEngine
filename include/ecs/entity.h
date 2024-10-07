#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

#define MAX_ENTITIES 1000 //Define Max Entities

typedef int Entity;  //Just an ID

Entity createEntity();
void destroyEntity(Entity entity);
bool isEntityAlive(Entity entity);

#endif
