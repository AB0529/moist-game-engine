#pragma once

#include <raylib.h>

typedef enum UIType { UIType_Gray = 1, UIType_Blue, UIType_Orange } UIType;
typedef enum UISlotType { UISlotType_Default = 1, UISlotType_Pushed, UISlotType_Trans } UISlotType;

typedef struct UIBase {
	UIType type;
	float scale;
	Rectangle spritesheet_location;
} UIBase;

typedef struct UISlot {
	UIType type;
	UISlotType slot_type;
	float scale;
	Rectangle spritesheet_location;
} UISlot;

UIBase init_ui_base(UIType type);
UISlot init_ui_slot(UIType ui_type, UISlotType slot_type);
