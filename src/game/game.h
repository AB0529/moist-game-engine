#pragma once

#include "engine/core/engine_context.h"
#include "game/game_context.h"

void game_init(EngineCtx* ctx, GameCtx* gctx);
void game_destroy(EngineCtx* ctx, GameCtx* gctx);
void game_update(EngineCtx* ctx, GameCtx* gctx);
void game_draw(EngineCtx* ctx, GameCtx* gctx);
