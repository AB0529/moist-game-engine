#pragma once

#include "engine/core/engine.h"

// Forward-declare EngineCtx to avoid circular includes; the implementation file
// includes the full engine_context.h.
typedef struct EngineCtx EngineCtx;

#include "engine/systems/assets_man.h"

#include <raylib.h>

UIInventorySettings init_ui_inventory_settings();
void draw_ui_inventory(AssetManager* am, UIInventory* u, Vector2 pos);
void update_ui_inventory(EngineCtx* ctx, UIInventory* u);

// set which UI color variant this inventory should use (UIType_Gray, _Blue, _Orange)
void ui_inventory_set_type(UIInventory* u, UIType type);

// UIPanel helpers (make inventory usable as a generic panel)
#include "engine/systems/ui_man.h"
UIPanel* ui_inventory_get_panel_template();
UIInventory* ui_inventory_create_state(Inventory* inv);
