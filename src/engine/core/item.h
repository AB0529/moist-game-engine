#pragma once

#include "engine/core/engine.h"

Item* item_init(Asset* asset, ItemType type, char* name);
Rectangle item_get_sprite_from_type(ItemType type);
