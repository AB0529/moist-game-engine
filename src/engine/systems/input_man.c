#include "input_man.h"

#include <math.h>
#include <raylib.h>
#include <string.h>

void input_init(InputManager* im) {
	memset(im, 0, sizeof(InputManager));
}
void input_destroy(InputManager* im) {}
void input_update(InputManager* im) {
	// Update key states
	for (int i = 0; i < InputManager_KeyCount; i++) {
		bool currently_down = IsKeyDown(InputManager_KeyMap[i]);
		im->pressed[i] = currently_down && !im->down[i];
		im->released[i] = !currently_down && im->down[i];
		im->down[i] = currently_down;
	}

	// Mouse
	im->mouse_x = GetMouseX();
	im->mouse_y = GetMouseY();
	im->mouse_left = IsMouseButtonDown(MOUSE_LEFT_BUTTON);
	im->mouse_right = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);

	// Determine MoveDir (priority: left/right > up/down)
	if (im->down[InputManager_Key_MoveLeft])
		im->move_dir = MoveDir_Left;
	else if (im->down[InputManager_Key_MoveRight])
		im->move_dir = MoveDir_Right;
	else if (im->down[InputManager_Key_MoveUp])
		im->move_dir = MoveDir_Up;
	else if (im->down[InputManager_Key_MoveDown])
		im->move_dir = MoveDir_Down;
	else
		im->move_dir = MoveDir_None;

	// Compute 2D movement vector
	im->move_vector.x = 0;
	im->move_vector.y = 0;

	if (im->down[InputManager_Key_MoveLeft])
		im->move_vector.x -= 1.0f;
	if (im->down[InputManager_Key_MoveRight])
		im->move_vector.x += 1.0f;
	if (im->down[InputManager_Key_MoveUp])
		im->move_vector.y -= 1.0f;
	if (im->down[InputManager_Key_MoveDown])
		im->move_vector.y += 1.0f;

	// Normalize vector if needed (prevents faster diagonal movement)
	float length =
	    sqrtf(im->move_vector.x * im->move_vector.x + im->move_vector.y * im->move_vector.y);
	if (length > 0) {
		im->move_vector.x /= length;
		im->move_vector.y /= length;
	}
}

bool is_player_moving(InputManager* im) {
	return im->move_dir != MoveDir_None;
}
