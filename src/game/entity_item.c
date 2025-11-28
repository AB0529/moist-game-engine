#include "engine/core/engine.h"
#include "engine/core/entity.h"
#include "engine/core/item.h"
#include "engine/systems/assets_man.h"
#include "game/game_context.h"
#include "game/inventory_man.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

EntityItem* entity_item_init(AssetManager* am, Item* item, Vector2 pos, float speed) {
	EntityItem* ei = malloc(sizeof(EntityItem));

	// Load assets
	Asset* item_asset = asset_get(am, "items_sprite");
	if (!item_asset) {
		printf("[ERROR] Failed to load item assets\n");
		free(ei);
		return NULL;
	}

	ei->item = item;
	ei->can_pickup = true;
	ei->is_dead = false;

	// Create entity name
	int len = snprintf(NULL, 0, "item-%d", ei->item->type) + 1;
	char* name = malloc(len);
	snprintf(name, len, "item-%d", ei->item->type);

	// Create entity
	ei->entity = entity_init(name, pos, ENTITY_TYPE_ITEM, speed);

	return ei;
}

void entity_item_destroy(EntityItem** e_ptr) {
	if (!e_ptr || !*e_ptr)
		return;

	EntityItem* e = *e_ptr;

	free(e->entity);

	free(e);
	*e_ptr = NULL;
}

void entity_item_update(AssetManager* am, EntityItem* e, GameCtx* gctx) {
	if (!e || e->is_dead)
		return;

	// Rotate to simulate dropped item
	if (e->entity->rotation >= 360)
		e->entity->rotation = 0;

	e->entity->rotation += 1;

	// Distance between player and item
	float dx = gctx->player->entity->pos.x - e->entity->pos.x;
	float dy = gctx->player->entity->pos.y - e->entity->pos.y;

	float distSq = dx * dx + dy * dy;

	// Radius in pixels
	float pickupRadius = 24.0f; // tweak this value
	float pickupRadiusSq = pickupRadius * pickupRadius;

	if (distSq <= pickupRadiusSq) {
		printf("AAA\n");
		inventory_item_add(gctx->player->entity->inventory, e->item);
		e->is_dead = true;

		return;
	}
}

void entity_item_draw(AssetManager* am, EntityItem* e) {
	if (!e || e->is_dead)
		return;

	Asset* sprite_sheet = asset_get(am, "items_sprite");
	if (!sprite_sheet)
		return;

	// Source rectangle (frame from sprite sheet)
	Rectangle source_rect = item_get_sprite_from_type(e->item->type);

	// Rotation origin = center of the sprite
	Vector2 origin = {source_rect.width / 2, source_rect.height / 2};

	// Destination rectangle (drawn on screen)
	Rectangle dest_rect = {.x = e->entity->pos.x,
	                       .y = e->entity->pos.y,
	                       .width = source_rect.width * 2,
	                       .height = source_rect.height * 2};

	DrawTexturePro(sprite_sheet->texture, source_rect, dest_rect, origin, e->entity->rotation,
	               WHITE);
}
