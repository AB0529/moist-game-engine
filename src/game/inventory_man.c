#include "inventory_man.h"

#include "engine/core/engine.h"
#include "engine/core/util.h"

#include <stdlib.h>
#include <string.h>

#define INVENTORY_INITAL_CAPACITY 8

Inventory* inventory_init() {
	Inventory* inv = malloc(sizeof(Inventory));

	inv->capacity = INVENTORY_INITAL_CAPACITY;
	inv->count = 0;
	inv->items = malloc(sizeof(Item*) * inv->capacity);
	inv->currently_selected = (Vector2){0, 0};

	return inv;
}

void inventory_destroy(Inventory* inv) {
	for (int i = 0; i < inv->count; i++) {
		free(inv->items[i]);
	}

	// Reset counts
	inv->capacity = 0;
	inv->count = 0;
}

void inventory_item_add(Inventory* inv, Item* item) {
	if (inv->count >= inv->capacity) {
		inv->capacity *= 2;
		inv->items = realloc(inv->items, sizeof(Item*) * inv->capacity);
	}

	inv->items[inv->count++] = item;
}

void inventory_item_remove(Inventory* inv, Item* item) {
	_remove_item((void**)inv->items, &inv->count, item);
}

Item* inventory_item_get(Inventory* inv, Item* item) {
	for (int i = 0; i < inv->count; i++) {

		if (inv->items[i] == item)
			return inv->items[i];
	}

	return NULL;
}
