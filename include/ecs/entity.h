#ifndef ENTITY_H
#define ENTITY_H

#include <stdbool.h>

#define MAX_ENTITIES 100000 //Define Max Entities

typedef int ECS_Entity;  //Just an ID

ECS_Entity ECS_create_entity();
void ECS_destroy_entity(ECS_Entity entity);
bool ECS_is_entity_alive(ECS_Entity entity);
void list_entities();

#endif
