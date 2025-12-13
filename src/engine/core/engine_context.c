#include "engine_context.h"

#include "engine/systems/entity_man.h"
#include "engine/systems/ui_man.h"

void engine_ctx_init(EngineCtx* ctx) {
	input_init(&ctx->input);
	asset_manager_init(&ctx->assets);
	entity_manager_init(&ctx->entities);
	ui_manager_init(&ctx->ui);
}

void engine_ctx_destroy(EngineCtx* ctx) {
	asset_manager_destroy(&ctx->assets);
	input_destroy(&ctx->input);
	entity_manager_destroy(&ctx->entities);
	// ui_manager_destroy(&ctx->ui);
}
