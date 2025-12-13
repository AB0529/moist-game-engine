#include "entity_player.h"

#include "engine/core/engine.h"
#include "engine/core/engine_context.h"
#include "engine/core/entity.h"
#include "engine/systems/assets_animation_man.h"
#include "engine/systems/assets_man.h"
#include "engine/systems/input_man.h"
#include "game/game_context.h"
#include "engine/systems/ui_inventory.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define CAMERA_LERP 0.10f

Player* player_init(EngineCtx* ctx, float start_x, float ground_y, float speed) {
	Player* p = malloc(sizeof(Player));
	if (!p)
		return NULL;

	// Load animations
	p->idle = asset_animation_get(&ctx->assets, "player_idle");
	p->walk = asset_animation_get(&ctx->assets, "player_walk");
	if (!p->idle || !p->walk) {
		printf("[ERROR] Failed to load player animations\n");
		free(p);
		return NULL;
	}

	// Set initial animation and facing
	p->current = p->idle;
	p->facing = Facing_Right;

	p->entity = entity_init("player", (Vector2){start_x, ground_y}, ENTITY_TYPE_PLAYER, speed);

	// Initialize camera to player feet
	p->camera.target = p->entity->pos;
	p->camera.offset = (Vector2){GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
	p->camera.rotation = 0.0f;
	p->camera.zoom = 1.0f;

	return p;
}

void player_destroy(Player* p) {
	if (!p)
		return;
	free(p->entity);
	free(p);
}

void player_update(Player* p, InputManager* im) {
	if (!p || !p->entity)
		return;

	// Normalize movement
	Vector2 move = im->move_vector;
	float mag = sqrtf(move.x * move.x + move.y * move.y);
	if (mag > 0) {
		move.x /= mag;
		move.y /= mag;
	}

	// Move player (pos = feet)
	float dt = GetFrameTime();
	p->entity->pos.x += move.x * p->entity->speed * dt;
	p->entity->pos.y += move.y * p->entity->speed * dt;

	// Update facing
	if (move.x < 0)
		p->facing = Facing_Left;
	else if (move.x > 0)
		p->facing = Facing_Right;

	// Update animation
	p->current = (mag > 0) ? p->walk : p->idle;
	animation_set_state(p->current, true, true);
	animation_update(p->current);

	// Flip animation horizontally
	p->current->frame_size.x = (p->facing == Facing_Left) ? -fabsf(p->current->frame_size.x)
	                                                      : fabsf(p->current->frame_size.x);

	// Smooth camera follows feet
	Vector2 target = p->entity->pos;
	p->camera.target.x += (target.x - p->camera.target.x) * CAMERA_LERP;
	p->camera.target.y += (target.y - p->camera.target.y) * CAMERA_LERP;
}

void player_draw(Player* p) {
	if (!p || !p->current)
		return;

	// Draw sprite: subtract texture height to align top-left with feet
	Vector2 draw_pos = {p->entity->pos.x, p->entity->pos.y - p->current->asset->texture.height};
	animation_draw(p->current, draw_pos);
}

void player_open_inventory(EngineCtx* ectx, GameCtx* gctx, Player* player) {
	if (!ectx || !gctx || !player)
		return;

	// Create a UIInventory state and open it as a panel
	UIInventory* ustate = ui_inventory_create_state(player->entity->inventory);
	if (!ustate)
		return;

	// Assign asset pointer from asset manager
	ustate->asset = asset_get(&ectx->assets, "ui_sprite");

	// Apply current UI color selection from engine/ui manager (gray/blue/orange)
	ustate->ui_type = ectx->ui.type;

	ui_manager_open_panel(ectx, ui_inventory_get_panel_template(), ustate);
}
