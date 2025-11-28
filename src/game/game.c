#include "game/game.h"

#include "engine/core/asset.h"
#include "engine/core/engine.h"
#include "engine/core/item.h"
#include "engine/systems/assets_animation_man.h"
#include "engine/systems/ui_man.h"
#include "game/entity_item.h"
#include "game/entity_player.h"
#include "game/inventory_man.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>

void game_spawn_item(GameCtx* gctx, EntityItem* item) {
	if (gctx->dropped_count >= gctx->dropped_capacity) {
		gctx->dropped_capacity *= 2;
		gctx->dropped_items =
		    realloc(gctx->dropped_items, sizeof(EntityItem*) * gctx->dropped_capacity);
	}

	gctx->dropped_items[gctx->dropped_count++] = item;
}

void game_load_assets(EngineCtx* ctx) {
	// Pre-load all the assets

	// Initialize assets
	Asset* items_sprite = asset_init("items_sprite", "assets/items_sheet.png", (Vector2){2, 2});
	Asset* player_idle = asset_init("player_idle", "assets/girl_idle_sheet.png", (Vector2){2, 2});
	Asset* player_walk = asset_init("player_walk", "assets/girl_walk_sheet.png", (Vector2){2, 2});
	Asset* ui_sprite_sheet =
	    asset_init("ui_sprite", "assets/ui_flat_spritesheet.png", (Vector2){1, 1});
	Asset* ui_select_sprite =
	    asset_init("ui_sprite_anim", "assets/ui_flat_spritesheet_animated.png", (Vector2){1, 1});

	// Add assets
	asset_add_asset(&ctx->assets, items_sprite);
	asset_add_asset(&ctx->assets, player_idle);
	asset_add_asset(&ctx->assets, player_walk);
	asset_add_asset(&ctx->assets, ui_sprite_sheet);
	asset_add_asset(&ctx->assets, ui_select_sprite);

	// Initialize animations
	AssetAnimation* idle_anim = animation_init(player_idle, 9, (Vector2){27, 72}, 0.3f);
	AssetAnimation* walk_anim = animation_init(player_walk, 12, (Vector2){36, 74}, 0.05f);
	AssetAnimation* ui_select_anim = animation_init(ui_select_sprite, 4, (Vector2){32, 32}, 0.15f);

	// Add animations
	asset_add_animation(&ctx->assets, idle_anim);
	asset_add_animation(&ctx->assets, walk_anim);
	asset_add_animation(&ctx->assets, ui_select_anim);

	printf("[Game] Assets preloaded.\n");
}
void game_init(EngineCtx* ctx, GameCtx* gctx) {
	engine_ctx_init(ctx);
	game_ctx_init(gctx);

	game_load_assets(ctx);

	Player* player = player_init(ctx, 100, 100, 150);
	gctx->player = player;

	Item* iron_ingot =
	    item_init(asset_get(&ctx->assets, "items_sprite"), ITEM_HAMMER_IRON, "iron_ingot");
	inventory_item_add(player->entity->inventory, iron_ingot);

	Item* i2 = item_init(asset_get(&ctx->assets, "items_sprite"), ITEM_APPLE, "idk");

	gctx->dropped_capacity = 16;
	gctx->dropped_count = 0;
	gctx->dropped_items = malloc(sizeof(EntityItem*) * gctx->dropped_capacity);

	// --- Initialize UI inventory ---
	gctx->ui_inventory.asset = asset_get(&ctx->assets, "ui_sprite");
	gctx->ui_inventory.inventory = NULL;
	gctx->ui_inventory.size = (Vector2){5, 5};
	gctx->ui_inventory.selected = (Vector2){0, 0};
	gctx->ui_inventory.settings = init_ui_inventory_settings();

	EntityItem* ingot_entity = entity_item_init(&ctx->assets, i2, (Vector2){500, 500}, 1);

	game_spawn_item(gctx, ingot_entity);
	printf("[Game] Initialized with Engine/Game Contexts.\n");
}

void game_destroy(EngineCtx* ctx, GameCtx* gctx) {
	engine_ctx_destroy(ctx);
	game_ctx_destroy(gctx);
	player_destroy(gctx->player);
	printf("[Game] System destroyed.\n");
}

void game_draw(EngineCtx* ctx, GameCtx* gctx) {
	player_draw(gctx->player);

	Vector2 ui_pos_world = {
	    gctx->player->camera.target.x - gctx->player->camera.offset.x + GetScreenWidth() / 2.0f,
	    gctx->player->camera.target.y - gctx->player->camera.offset.y + GetScreenHeight() / 2.0f};

	switch (gctx->ui_state) {
		case UI_VENDOR:
		case UI_INVENTORY:
			draw_ui_inventory(ctx, &gctx->ui_inventory,
			                  (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2});
			break;

		default:
		case UI_NONE:
			break;
	}

	for (int i = 0; i < gctx->dropped_count; i++) {
		EntityItem* e = gctx->dropped_items[i];
		if (e && !e->is_dead)
			entity_item_draw(&ctx->assets, e);
	}
}

void game_update(EngineCtx* ctx, GameCtx* gctx) {
	input_update(&ctx->input);

	if (ctx->input.down[InputManager_Key_Inventory_Open]) {
		player_open_inventory(gctx, gctx->player);
	}

	if (gctx->ui_state != UI_NONE && ctx->input.down[InputManager_Key_UI_Close]) {
		gctx->ui_state = UI_NONE;
		return;
	}

	if (gctx->ui_state != UI_NONE) {
		update_ui_inventory(ctx, &gctx->ui_inventory);
		return;
	} else {
		player_update(gctx->player, &ctx->input);
	}

	// Update all items
	for (int i = 0; i < gctx->dropped_count; i++) {
		EntityItem* e = gctx->dropped_items[i];

		if (!e || e->is_dead)
			continue;

		entity_item_update(&ctx->assets, e, gctx);
	}

	// Purge dead items
	for (int i = 0; i < gctx->dropped_count;) {
		EntityItem* e = gctx->dropped_items[i];

		if (e && e->is_dead) {
			entity_item_destroy(&e);
			gctx->dropped_items[i] = gctx->dropped_items[--gctx->dropped_count];
		} else {
			i++;
		}
	}
}
