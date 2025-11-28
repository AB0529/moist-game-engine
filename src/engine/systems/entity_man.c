#include "entity_man.h"

#include "engine/core/engine.h"
#include "engine/core/util.h"

#include <stdlib.h>
#include <string.h>

#define ENTITY_MANAGER_INITAL_CAPACITY 8

void entity_manager_init(EntityManager* em) {
	// Initialize entityies
	em->count = 0;
	em->capacity = ENTITY_MANAGER_INITAL_CAPACITY;
	em->entities = malloc(sizeof(Entity*) * em->capacity);
}

void entity_manager_destroy(EntityManager* em) {
	// Free entities
	for (int i = 0; i < em->count; i++) {
		free(em->entities[i]);
	}
	free(em->entities);

	// Reset counts and capacities
	em->count = 0;
	em->capacity = 0;
}

static void _entity_manager_resize_entities(EntityManager* em) {
	em->capacity *= 2;
	em->entities = realloc(em->entities, sizeof(Entity*) * em->capacity);
}

void entity_add(EntityManager* em, Entity* e) {
	if (em->count >= em->capacity) {
		_entity_manager_resize_entities(em);
	}

	em->entities[em->count++] = e;
}

void entity_remove(EntityManager* em, Entity* e) {
	_remove_item((void**)em->entities, &em->count, e);
}

Entity* entity_get(EntityManager* em, const char* name) {
	for (int i = 0; i < em->count; i++) {
		if (strcmp(em->entities[i]->name, name) == 0) {
			return em->entities[i];
		}
	}

	return NULL;
}
