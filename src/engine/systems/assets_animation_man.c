#include "engine/core/engine.h"

#include <raylib.h>
#include <stdlib.h>

AssetAnimation* animation_init(Asset* asset, int frame_count, Vector2 frame_size,
                               float frame_duration) {
	AssetAnimation* anim = malloc(sizeof(*anim));
	*anim = (AssetAnimation){.asset = asset,
	                         .frame_count = frame_count,
	                         .frame_size = frame_size,
	                         .frame_duration = frame_duration,
	                         .play = true,
	                         .loop = true,
	                         .current_frame = 0,
	                         .frame_timer = 0.0f};
	return anim;
}

void animation_set_frame(AssetAnimation* am, int frame) {
	if (frame >= 0 && frame < am->frame_count) {
		am->current_frame = frame;
		am->frame_timer = 0;
	}
}

void animation_next_frame(AssetAnimation* am) {
	am->current_frame++;
	if (am->current_frame >= am->frame_count)
		am->current_frame = (am->loop ? 0 : am->frame_count - 1);
}

void animation_prev_frame(AssetAnimation* am) {
	am->current_frame--;
	if (am->current_frame < 0)
		am->current_frame = (am->loop ? am->frame_count - 1 : 0);
}

// Updates the animation
void animation_update(AssetAnimation* am) {
	if (!am->play)
		return; // Manual mode

	am->frame_timer += GetFrameTime();

	if (am->frame_timer >= am->frame_duration) {
		am->frame_timer = 0.0;
		am->current_frame++;

		if (am->current_frame >= am->frame_count) {
			am->current_frame = (am->loop ? 0 : am->frame_count - 1);
		}
	}
}

// Draws the current frame with a destination rectangle (allows scaling)
void animation_draw(const AssetAnimation* am, Vector2 position) {
	const float INITIAL_OFFSET = 0;
	const float FRAME_GAP = 0;
	const Vector2 scale = (Vector2){1 * am->asset->scale.x, 1 * am->asset->scale.y};

	float frame_x_offset = INITIAL_OFFSET + am->current_frame * (am->frame_size.x + FRAME_GAP);

	// Source rectangle (the frame inside the sprite sheet)
	Rectangle source_rect = {
	    .x = frame_x_offset, .y = 0, .width = am->frame_size.x, .height = am->frame_size.y};

	// Destination rectangle (scaled area on screen)
	Rectangle dest_rect = {.x = position.x,
	                       .y = position.y,
	                       .width = am->frame_size.x * scale.x,
	                       .height = am->frame_size.y * scale.y};

	// Draw the frame scaled into the destination rectangle
	DrawTexturePro(am->asset->texture, source_rect, dest_rect, (Vector2){0, 0}, am->asset->rotation,
	               WHITE);
}

void animation_set_state(AssetAnimation* anim, bool play, bool loop) {
	anim->play = play;
	anim->loop = loop;
}
