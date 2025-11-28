
#include "item.h"

#include "engine/core/engine.h"

#include <raylib.h>
#include <stdlib.h>

Item* item_init(Asset* asset, ItemType type, char* name) {
	Item* item = malloc(sizeof(Item));

	item->asset = asset;
	item->type = type;
	item->count = 1;
	item->name = name;

	return item;
}

Vector2 item_get_sprite_xy_from_index(int x, int y) {
	return (Vector2){x * 16, y * 16};
}

Rectangle item_get_sprite_from_type(ItemType type) {
	int sprite_w = 16;
	int sprite_h = 16;

	int x = type % 8;
	int y = type / 8;

	Vector2 pos = item_get_sprite_xy_from_index(x, y);

	return (Rectangle){.x = pos.x, .y = pos.y, .width = sprite_w, .height = sprite_h};
}
