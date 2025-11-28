#include "game_context.h"

void game_ctx_init(GameCtx* ctx) {
	ctx->is_paused = false;
	ctx->ui_state = UI_NONE;
}

void game_ctx_destroy(GameCtx* ctx) {}
