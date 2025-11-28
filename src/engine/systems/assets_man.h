#pragma once

#include "../core/engine.h"

typedef struct AssetManager {
	Asset** assets;
	int assets_count;
	int assets_capacity;

	AssetAnimation** asset_animations;
	int animation_count;
	int animation_capacity;

} AssetManager;

void asset_manager_init(AssetManager* am);

void asset_add_asset(AssetManager* am, Asset* asset);
void asset_add_animation(AssetManager* am, AssetAnimation* ani);

void asset_remove_asset(AssetManager* am, Asset* asset);
void asset_remove_animation(AssetManager* am, AssetAnimation* ani);

void asset_manager_destroy(AssetManager* am);

Asset* asset_get(AssetManager* am, const char* name);
AssetAnimation* asset_animation_get(AssetManager* am, const char* name);
void asset_destroy(Asset* a);
void asset_animation_destroy(AssetAnimation* a);
