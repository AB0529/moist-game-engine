#pragma once

#include "../systems/assets_man.h"
#include "../systems/input_man.h"
#include "engine/systems/entity_man.h"
#include "engine/systems/ui_man.h"

typedef struct EngineCtx {
	InputManager input;
	AssetManager assets;
	EntityManager entities;
	UIManager ui;
} EngineCtx;

void engine_ctx_init(EngineCtx* ctx);
void engine_ctx_destroy(EngineCtx* ctx);
