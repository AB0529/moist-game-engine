#include "game_context.h"

void game_ctx_init(GameCtx* ctx) {
	ctx->is_paused = false;
}

void game_ctx_destroy(GameCtx* ctx) {}
