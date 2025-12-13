#pragma once

#include "engine/core/engine.h"

#include <raylib.h>

typedef enum { Facing_Left, Facing_Right } Facing;

typedef struct Player {
	Entity* entity;
	AssetAnimation* idle;
	AssetAnimation* walk;
	AssetAnimation* current;
	Facing facing;
	Camera2D camera;
} Player;

typedef struct EntityItem {
	Entity* entity;
	Item* item;
	// TODO: maybe make this into a bit flag system later
	bool can_pickup;
	bool is_dead;
} EntityItem;

typedef struct GameCtx {
	bool is_paused;
	Player* player;

	EntityItem** dropped_items;
	int dropped_count;
	int dropped_capacity;
} GameCtx;

void game_ctx_init(GameCtx* ctx);
void game_ctx_destroy(GameCtx* ctx);
