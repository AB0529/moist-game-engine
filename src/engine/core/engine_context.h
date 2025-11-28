#pragma once

#include "../systems/assets_man.h"
#include "../systems/input_man.h"
#include "engine/systems/entity_man.h"

typedef struct EngineCtx {
	InputManager input;
	AssetManager assets;
	EntityManager entities;
} EngineCtx;

void engine_ctx_init(EngineCtx* ctx);
void engine_ctx_destroy(EngineCtx* ctx);
