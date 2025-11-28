#include "engine/core/engine.h"
#include "engine/core/item.h"
#include "engine/systems/assets_man.h"
#include "game/entity_item.h"
#include "game/game.h"
#include "game/game_context.h"

#include <raylib.h>

int main() {
	InitWindow(1080, 720, "The Game");
	SetTargetFPS(60);

	GameCtx gctx;
	EngineCtx ectx;

	game_init(&ectx, &gctx);

	while (!WindowShouldClose()) {
		input_update(&ectx.input);

		game_update(&ectx, &gctx);

		BeginDrawing();
		BeginMode2D(gctx.player->camera);
		ClearBackground(GRAY);
		game_draw(&ectx, &gctx);

		EndMode2D();

		// Debug texts (screen-space)
		DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, BLACK);

		DrawText(TextFormat("Player Pos: (%.2f, %.2f)", gctx.player->entity->pos.x,
		                    gctx.player->entity->pos.y),
		         10, 40, 20, BLACK);

		EndDrawing();
	}

	game_destroy(&ectx, &gctx);
	CloseWindow();
}
