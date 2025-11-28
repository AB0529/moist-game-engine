#include "entity.h"

#include "engine/core/engine.h"
#include "game/inventory_man.h"

#include <stdlib.h>

Entity* entity_init(char* name, Vector2 pos, EntityType type, float speed) {
	Entity* e = malloc(sizeof(Entity));

	e->pos = pos;
	e->name = name;
	e->type = type;
	e->rotation = 0;
	e->inventory = inventory_init();
	e->speed = speed;

	return e;
}
