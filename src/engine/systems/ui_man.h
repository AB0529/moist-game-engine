#pragma once

#include "engine/core/engine.h"
#include "engine/systems/assets_man.h"

// Forward declare EngineCtx to avoid circular include (engine_context.h includes this header)
typedef struct EngineCtx EngineCtx;

typedef enum UIState { UIState_None, UIState_Inventory, UIState_Vendor } UIState;

typedef struct UIManager {
	UIState state;
	UIType type;
	struct UIPanel* active_panel;
	void* active_panel_state;
} UIManager;
UIManager* ui_manager_init(UIManager* ui_man);
void ui_manager_destroy(UIManager* ui_man);

// Generic panel abstraction for reusable UIs
typedef struct UIPanel {
	void (*draw)(EngineCtx* ctx, void* state);
	void (*update)(EngineCtx* ctx, void* state);
	void (*on_close)(void* state);
	bool draw_overlay; // whether to dim background when this panel is active
} UIPanel;

void ui_manager_draw(EngineCtx* ctx, UIManager* ui_man);
void ui_manager_update(EngineCtx* ctx, UIManager* ui_man);

// Open a UIPanel with an optional state pointer owned by the caller. The UI manager
// will call the panel's on_close(state) when the panel is closed, if provided.
void ui_manager_open_panel(EngineCtx* ctx, UIPanel* panel, void* state);
void ui_manager_close(EngineCtx* ctx);
