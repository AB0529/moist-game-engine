#pragma once

#include "engine/core/engine.h"
#include "engine/core/engine_context.h"

#include <raylib.h>

UIInventorySettings init_ui_inventory_settings();
void draw_ui_inventory(EngineCtx* ctx, UIInventory* u, Vector2 pos);
void update_ui_inventory(EngineCtx* ctx, UIInventory* u);
