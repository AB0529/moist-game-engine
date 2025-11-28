#pragma once
#include "engine/core/engine.h"
#include "engine/systems/assets_man.h"
#include "game/game_context.h"

#include <raylib.h>

EntityItem* entity_item_init(AssetManager* am, Item* item, Vector2 pos, float speed);
void entity_item_destroy(EntityItem** entity);
void entity_item_update(AssetManager* am, EntityItem* entity, GameCtx* gctx);
void entity_item_draw(AssetManager* am, EntityItem* entity);
