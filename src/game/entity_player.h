#pragma once
#include "engine/core/engine_context.h"
#include "engine/systems/input_man.h"
#include "game/game_context.h"

#include <raylib.h>

Player* player_init(EngineCtx* ctx, float start_x, float start_y, float speed);
void player_destroy(Player* player);
void player_update(Player* player, InputManager* im);
void player_draw(Player* player);
void player_open_inventory(EngineCtx* ectx, GameCtx* gctx, Player* player);
