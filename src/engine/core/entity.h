#pragma once

#include "engine/core/engine.h"

#include <raylib.h>

Entity* entity_init(char* name, Vector2 pos, EntityType type, float speed);
