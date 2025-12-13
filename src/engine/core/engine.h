#pragma once

#include <raylib.h>

typedef enum { ENTITY_TYPE_PLAYER = 0, ENTITY_TYPE_ITEM, ENTITY_TYPE_COUNT } EntityType;

typedef enum {
	ITEM_HOOK_IRON = 0,
	ITEM_HOOK_GOLD,
	ITEM_HOOK_WOOD,
	ITEM_HOOK_BONE,
	ITEM_DAGGER_IRON,
	ITEM_DAGGER_GOLD,
	ITEM_DAGGER_WOOD,
	ITEM_DAGGER_BONE,

	ITEM_SPEAR_IRON,
	ITEM_SPEAR_GOLD,
	ITEM_SPEAR_WOOD,
	ITEM_SPEAR_BONE,
	ITEM_AXE_IRON,
	ITEM_AXE_GOLD,
	ITEM_AXE_WOOD,
	ITEM_AXE_BONE,

	ITEM_PICKAXE_IRON,
	ITEM_PICKAXE_GOLD,
	ITEM_PICKAXE_WOOD,
	ITEM_PICKAXE_BONE,
	ITEM_HAMMER_IRON,
	ITEM_HAMMER_GOLD,
	ITEM_HAMMER_WOOD,
	ITEM_HAMMER_BONE,

	ITEM_WAND_WOOD,
	ITEM_WAND_CRYSTAL,
	ITEM_WAND_EMERALD,
	ITEM_WAND_AMETHYST,
	ITEM_BOW_WOOD,
	ITEM_BOW_GOLD,
	ITEM_BOW_COMPOUND,
	ITEM_BOW_CURVED,

	ITEM_CLAW,
	ITEM_SHIELD_WOOD,
	ITEM_SHIELD_IRON,
	ITEM_SHIELD_GOLD,
	ITEM_PORTRAIT,
	ITEM_HELM_RED,
	ITEM_HELM_IRON,
	ITEM_SKULL,

	ITEM_AMULET_GOLD,
	ITEM_AMULET_SILVER,
	ITEM_RING_GOLD,
	ITEM_RING_SILVER,
	ITEM_RING_EMERALD,
	ITEM_RING_RUBY,
	ITEM_GEM_BLUE,
	ITEM_GEM_RED,

	ITEM_SCROLL_BASIC,
	ITEM_SCROLL_ADVANCED,
	ITEM_BOOK_BLUE,
	ITEM_BOOK_RED,
	ITEM_LOG,
	ITEM_WOOD_PLANK,
	ITEM_WOOD_BUNDLE,
	ITEM_ORE_IRON,

	ITEM_BUCKET_WATER,
	ITEM_MEAT,
	ITEM_BREAD,
	ITEM_CHEESE,
	ITEM_LEAF_GREEN,
	ITEM_LEAF_DARK,
	ITEM_LEAF_LIGHT,
	ITEM_BANANA,

	ITEM_CARROT,
	ITEM_CHILI,
	ITEM_BERRIES,
	ITEM_APPLE,
	ITEM_PEPPER,
	ITEM_MUSHROOM,
	ITEM_HERB,
	ITEM_FLOWER,

	ITEM_TYPE_COUNT
} ItemType;

typedef struct Asset {
	char* path;
	char* name;
	Texture2D texture;
	Vector2 scale;
	float rotation;
} Asset;

typedef struct AssetAnimation {
	Asset* asset;
	int frame_count;
	Vector2 frame_size;
	double frame_duration;
	bool can_advance_next;
	bool can_advance_prev;
	int current_frame;
	double frame_timer;
	bool play;
	bool loop;
} AssetAnimation;

typedef struct Item {
	ItemType type;
	char* name;
	int count;
	Asset* asset;
} Item;

typedef struct Inventory {
	Item** items;
	int count;
	int capacity;
	Vector2 currently_selected;
} Inventory;

typedef struct Entity {
	Vector2 pos;
	char* name;
	EntityType type;
	float speed;
	float rotation;
	Inventory* inventory;
} Entity;

typedef struct UIInventorySettings {
	Rectangle src_base; // spritesheet rect for the base frame
	Rectangle src_slot; // spritesheet rect for a slot

	float scale;     // global UI scaling
	float pad;       // outer padding
	float spacing_x; // space between slots horizontally
	float spacing_y; // space between slots vertically

	float slot_w; // scaled slot width
	float slot_h; // scaled slot height

	float base_x; // screen position of UI
	float base_y; // screen position of UI
} UIInventorySettings;
// UI color variants available in the UI spritesheet
typedef enum UIType { UIType_Gray = 1, UIType_Blue, UIType_Orange } UIType;

typedef struct UIInventory {
	Asset* asset;
	Inventory* inventory;
	Vector2 size;
	Vector2 selected;
	UIInventorySettings settings;
	UIType ui_type; // color variant for this UI (uses UIType enum)
} UIInventory;

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
