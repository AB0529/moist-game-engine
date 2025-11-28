#include "ui.h"

#include <raylib.h>

UIBase init_ui_base(UIType type) {
	Rectangle base_rect = (Rectangle){32, 32, 96, 64};

	UIBase base = {
		.type = type,
		.scale = 1,
		.spritesheet_location = (Rectangle){
		    base_rect.x * type,
		    base_rect.y * type,
		    base_rect.height,
		    base_rect.width,
		};

	return base;
}

UISlot init_ui_slot(UIType ui_type, UISlotType slot_type) {
	Rectangle base_rect = (Rectangle){32, 128, 32, 32};

	UISlot base = {.type = ui_type,
	               .slot_type = slot_type.scale = 1,
	               .spritesheet_location = (Rectangle){
	                   base_rect.x * ui_type,
	                   base_rect.y * slot_type,
	                   base_rect.height,
	                   base_rect.width,
	               }};

	return base;
}
