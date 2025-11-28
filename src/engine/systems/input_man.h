#pragma once

#include <raylib.h>

typedef enum { MoveDir_None = 0, MoveDir_Left, MoveDir_Right, MoveDir_Up, MoveDir_Down } MoveDir;

typedef enum {
	// Movement keys
	InputManager_Key_MoveLeft,
	InputManager_Key_MoveRight,
	InputManager_Key_MoveUp,
	InputManager_Key_MoveDown,
	// Misc.
	InputManager_Key_Menu,
	InputManager_Key_Inventory_Open,
	// UI Movement
	InputManager_Key_UI_MoveLeft,
	InputManager_Key_UI_MoveRight,
	InputManager_Key_UI_MoveUp,
	InputManager_Key_UI_MoveDown,
	InputManager_Key_UI_Close,

	InputManager_KeyCount
} InputManager_Keys;

static int InputManager_KeyMap[InputManager_KeyCount] = {
    [InputManager_Key_MoveLeft] = KEY_A,
    [InputManager_Key_MoveRight] = KEY_D,
    [InputManager_Key_MoveUp] = KEY_W,
    [InputManager_Key_MoveDown] = KEY_S,
    [InputManager_Key_Menu] = KEY_M,
    [InputManager_Key_UI_MoveLeft] = KEY_LEFT,
    [InputManager_Key_UI_MoveRight] = KEY_RIGHT,
    [InputManager_Key_UI_MoveUp] = KEY_UP,
    [InputManager_Key_UI_MoveDown] = KEY_DOWN,
    [InputManager_Key_UI_Close] = KEY_Q,
    [InputManager_Key_Inventory_Open] = KEY_I,
};

typedef struct InputManager {
	bool down[InputManager_KeyCount];
	bool pressed[InputManager_KeyCount];
	bool released[InputManager_KeyCount];

	int mouse_x, mouse_y;
	bool mouse_left;
	bool mouse_right;
	MoveDir move_dir;
	Vector2 move_vector;
} InputManager;

void input_init(InputManager* im);
void input_update(InputManager* im);
void input_destroy(InputManager* im);
bool is_player_moving(InputManager* im);
