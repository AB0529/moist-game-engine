#pragma once

#include "engine/core/engine.h"

#include <raylib.h>

AssetAnimation* animation_init(Asset* asset, int frame_count, Vector2 frame_size,
                               float frame_duration);
void animation_update(AssetAnimation* am);
void animation_draw(AssetAnimation* am, Vector2 position);
void animation_set_frame(AssetAnimation* am, int frame);
void animation_next_frame(AssetAnimation* am);
void animation_prev_frame(AssetAnimation* am);
void animation_set_state(AssetAnimation* anim, bool play, bool loop);
