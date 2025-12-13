#include "ui_inventory.h"

#include "engine/core/engine.h"
#include "engine/core/engine_context.h"
#include "engine/core/item.h"
#include "engine/systems/assets_animation_man.h"
#include "engine/systems/assets_man.h"

#include <raylib.h>
#include <stdlib.h>

UIInventorySettings init_ui_inventory_settings() {
    UIInventorySettings s = {0};

    s.src_base = (Rectangle){32, 32, 96, 64};
    s.src_slot = (Rectangle){32, 128, 32, 32};

    s.scale = 0.5f;

    s.pad = 25 * s.scale;
    s.spacing_x = 5 * s.scale;
    s.spacing_y = 5 * s.scale;

    s.slot_w = s.src_slot.width * 4 * s.scale;
    s.slot_h = s.src_slot.height * 4 * s.scale;

    s.base_x = 100 * s.scale;
    s.base_y = 100 * s.scale;

    return s;
}

void draw_ui_inventory(AssetManager* am, UIInventory* u, Vector2 pos) {
    if (!u || !u->inventory)
        return;

    UIInventorySettings s = u->settings;
    Inventory* inv = u->inventory;

    int rows = (int)u->size.y;
    int cols = (int)u->size.x;

    // --- TEXTURE ---
    Texture2D uiTex = u->asset->texture;

    // --- COMPUTE BASE SIZE ---
    float base_w = s.pad * 2 + cols * s.slot_w + (cols - 1) * s.spacing_x;
    float base_h = s.pad * 2 + rows * s.slot_h + (rows - 1) * s.spacing_y;

    pos = (Vector2){pos.x - base_w / 2, pos.y - base_h / 2};

    // --- DRAW BASE PANEL ---
    // support color variants: the spritesheet stores variants in columns.
    // Compute an x-offset stride per variant instead of naively multiplying x/y.
    // Empirically the UI blocks are spaced by ~128px horizontally in the spritesheet,
    // so pick that as the stride (96px width + padding). This keeps base y/slot y unchanged.
    int variant = (u->ui_type > 0) ? (int)u->ui_type : 1;
    const int variant_stride_x = 128;
    Rectangle src_base = s.src_base;
    Rectangle src_slot = s.src_slot;
    src_base.x = src_base.x + (variant - 1) * variant_stride_x;
    src_slot.x = src_slot.x + (variant - 1) * variant_stride_x;

    DrawTexturePro(uiTex, src_base,
                   (Rectangle){pos.x, pos.y, base_w, base_h}, // position now uses pos
                   (Vector2){0, 0},                           // origin top-left
                   u->asset->rotation, WHITE);

    // --- GRID ORIGIN (relative to pos) ---
    float grid_x = pos.x + s.pad;
    float grid_y = pos.y + s.pad;

    // --- DRAW SLOTS + ITEMS ---
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            float px = grid_x + c * (s.slot_w + s.spacing_x);
            float py = grid_y + r * (s.slot_h + s.spacing_y);

            // Draw slot frame (use variant src)
            DrawTexturePro(uiTex, src_slot, (Rectangle){px, py, s.slot_w, s.slot_h},
                           (Vector2){0, 0}, 0, WHITE);

            // Draw item if present
            int index = r * cols + c;
            if (index >= inv->count)
                continue;

            Item* item = inv->items[index];
            if (!item)
                continue;

            Asset* item_asset = item->asset;
            Rectangle src_icon = item_get_sprite_from_type(item->type);

            float icon_w = src_icon.width * 5 * s.scale;
            float icon_h = src_icon.height * 5 * s.scale;

            DrawTexturePro(item_asset->texture, src_icon,
                           (Rectangle){px + (s.slot_w - icon_w) / 2, py + (s.slot_h - icon_h) / 2,
                                       icon_w, icon_h},
                           (Vector2){0, 0}, 0, WHITE);
        }
    }

    // --- DRAW SELECTION HIGHLIGHT ---
    Vector2 selected = u->selected;

    AssetAnimation* sel_anim = asset_animation_get(am, "ui_sprite_anim");
    animation_update(sel_anim);

    // Scale highlight to slot size
    sel_anim->asset->scale =
        (Vector2){s.slot_w / sel_anim->frame_size.x, s.slot_h / sel_anim->frame_size.y};

    float sel_x = grid_x + selected.x * (s.slot_w + s.spacing_x);
    float sel_y = grid_y + selected.y * (s.slot_h + s.spacing_y);

    animation_draw(sel_anim, (Vector2){sel_x, sel_y});
}

// TODO: move this into UIInventory settings
#define MOVE_DELAY 0.2f
static float move_timer_x = 0;
static float move_timer_y = 0;

void update_ui_inventory(EngineCtx* ctx, UIInventory* u) {
    Vector2* selected = &u->selected;
    float dt = GetFrameTime();

    // Horizontal
    if (ctx->input.pressed[InputManager_Key_UI_MoveLeft] ||
        (ctx->input.down[InputManager_Key_UI_MoveLeft] && move_timer_x <= 0)) {
        if (selected->x > 0)
            selected->x--;
        move_timer_x = MOVE_DELAY;
    }
    if (ctx->input.pressed[InputManager_Key_UI_MoveRight] ||
        (ctx->input.down[InputManager_Key_UI_MoveRight] && move_timer_x <= 0)) {
        if (selected->x < u->size.x - 1)
            selected->x++;
        move_timer_x = MOVE_DELAY;
    }

    // Vertical
    if (ctx->input.pressed[InputManager_Key_UI_MoveUp] ||
        (ctx->input.down[InputManager_Key_UI_MoveUp] && move_timer_y <= 0)) {
        if (selected->y > 0)
            selected->y--;
        move_timer_y = MOVE_DELAY;
    }
    if (ctx->input.pressed[InputManager_Key_UI_MoveDown] ||
        (ctx->input.down[InputManager_Key_UI_MoveDown] && move_timer_y <= 0)) {
        if (selected->y < u->size.y - 1)
            selected->y++;
        move_timer_y = MOVE_DELAY;
    }

    // Decrease timers
    move_timer_x -= dt;
    move_timer_y -= dt;
}

// --- UIPanel adapter ---
// Panel draw wrapper: expects state to be a UIInventory*
static void ui_inventory_panel_draw(EngineCtx* ctx, void* state) {
    UIInventory* u = (UIInventory*)state;
    if (!u)
        return;

    Vector2 center = (Vector2){GetScreenWidth() / 2, GetScreenHeight() / 2};
    draw_ui_inventory(&ctx->assets, u, center);
}

static void ui_inventory_panel_update(EngineCtx* ctx, void* state) {
    UIInventory* u = (UIInventory*)state;
    if (!u)
        return;
    update_ui_inventory(ctx, u);
}

static void ui_inventory_panel_on_close(void* state) {
    UIInventory* u = (UIInventory*)state;
    if (!u)
        return;
    // Don't free Inventory* (owned by game); free only UIInventory wrapper if allocated
    free(u);
}

// Expose a UIPanel template for inventory
UIPanel* ui_inventory_get_panel_template() {
    static UIPanel panel = {0};
    static bool init = false;
    if (!init) {
        panel.draw = ui_inventory_panel_draw;
        panel.update = ui_inventory_panel_update;
        panel.on_close = ui_inventory_panel_on_close;
        panel.draw_overlay = true;
        init = true;
    }
    return &panel;
}

// Helper to create UIInventory state for a player's inventory. Caller becomes owner
UIInventory* ui_inventory_create_state(Inventory* inv) {
    UIInventory* u = malloc(sizeof(UIInventory));
    if (!u)
        return NULL;
    u->asset = NULL; // caller should set the asset from AssetManager
    u->inventory = inv;
    u->size = (Vector2){5, 5};
    u->selected = (Vector2){0, 0};
    u->settings = init_ui_inventory_settings();
    u->ui_type = UIType_Gray; // sensible default
    return u;
}

void ui_inventory_set_type(UIInventory* u, UIType type) {
    if (!u)
        return;
    if (type < UIType_Gray || type > UIType_Orange)
        return;
    u->ui_type = type;
}
