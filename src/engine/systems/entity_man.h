#pragma once

#include "../core/engine.h"

typedef struct EntityManager {
	Entity** entities;
	int count;
	int capacity;
} EntityManager;

void entity_manager_init(EntityManager* em);
void entity_manager_destroy(EntityManager* em);
void entity_add(EntityManager* em, Entity* e);
void entity_remove(EntityManager* em, Entity* e);
Entity* entity_get(EntityManager* em, const char* name);
