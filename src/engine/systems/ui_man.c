#include "engine/systems/ui_man.h"

#include "engine/core/engine.h"
#include "engine/core/engine_context.h"
#include "engine/systems/assets_man.h"
#include "engine/systems/ui_inventory.h"

#include <stdlib.h>

UIManager* ui_manager_init(UIManager* ui_man) {
	ui_man->state = UIState_None;
	ui_man->type = UIType_Gray;

	ui_man->active_panel = NULL;
	ui_man->active_panel_state = NULL;

	return ui_man;
}

void ui_manager_destroy(UIManager* ui_man) {
	(void)ui_man;
}

void ui_manager_draw(EngineCtx* ctx, UIManager* ui_man) {
	switch (ui_man->state) {
		case UIState_Inventory: {
			// If active panel requests overlay, draw it
			if (ui_man->active_panel && ui_man->active_panel->draw_overlay) {
				DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.7f));
			}

			// If we have an active panel, call its draw callback
			if (ui_man->active_panel && ui_man->active_panel->draw) {
				ui_man->active_panel->draw(ctx, ui_man->active_panel_state);
			}
			break;
		}

		default:
		case UIState_None: {

			break;
		}
	}
}

void ui_manager_update(EngineCtx* ctx, UIManager* ui_man) {
	// Forward update to active panel if present
	if (ui_man->active_panel && ui_man->active_panel->update) {
		ui_man->active_panel->update(ctx, ui_man->active_panel_state);
	}
}

void ui_manager_open_panel(EngineCtx* ctx, UIPanel* panel, void* state) {
	if (!ctx)
		return;

	// Close existing panel first
	if (ctx->ui.active_panel) {
		if (ctx->ui.active_panel->on_close && ctx->ui.active_panel_state)
			ctx->ui.active_panel->on_close(ctx->ui.active_panel_state);
	}

	ctx->ui.active_panel = panel;
	ctx->ui.active_panel_state = state;
	ctx->ui.state = UIState_Inventory; // treat generic panel as modal inventory-like state
}

void ui_manager_close(EngineCtx* ctx) {
	if (!ctx)
		return;

	if (ctx->ui.active_panel && ctx->ui.active_panel->on_close && ctx->ui.active_panel_state) {
		ctx->ui.active_panel->on_close(ctx->ui.active_panel_state);
	}

	ctx->ui.active_panel = NULL;
	ctx->ui.active_panel_state = NULL;
	ctx->ui.state = UIState_None;
}
