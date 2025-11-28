#pragma once

#include "../engine/core/engine.h"

Inventory* inventory_init();
void inventory_destroy(Inventory* inv);
void inventory_item_add(Inventory* inv, Item* item);
void inventory_item_remove(Inventory* inv, Item* item);
Item* inventory_item_get(Inventory* inv, Item* item);
