#include "assets_man.h"

#include "engine/core/engine.h"
#include "engine/core/util.h"

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ASSET_MANAGER_INITAL_CAPACITY 8

void asset_manager_init(AssetManager* am) {
	// Initialize assets
	am->assets_count = 0;
	am->assets_capacity = ASSET_MANAGER_INITAL_CAPACITY;
	am->assets = malloc(sizeof(Asset*) * am->assets_capacity);

	// Initialize animations
	am->animation_count = 0;
	am->animation_capacity = ASSET_MANAGER_INITAL_CAPACITY;
	am->asset_animations = malloc(sizeof(AssetAnimation*) * am->animation_capacity);
}

static void _asset_manager_resize_assets(AssetManager* am) {
	am->assets_capacity *= 2;
	Asset** tmp = realloc(am->assets, sizeof(Asset*) * am->assets_capacity);
	if (!tmp) {
		fprintf(stderr, "[FATAL] Failed to resize asset array\n");
		exit(1);
	}
	am->assets = tmp;
}

static void _asset_manager_resize_anims(AssetManager* am) {
	am->animation_capacity *= 2;
	am->asset_animations =
	    realloc(am->asset_animations, sizeof(AssetAnimation*) * am->animation_capacity);
}

void asset_add_asset(AssetManager* am, Asset* asset) {
	// Make sure texture is loaded
	if (asset->texture.id < 0)
		return;

	if (am->assets_count >= am->assets_capacity) {
		_asset_manager_resize_assets(am);
	}

	am->assets[am->assets_count++] = asset;
}

void asset_add_animation(AssetManager* am, AssetAnimation* anim) {
	if (am->animation_count >= am->animation_capacity) {
		_asset_manager_resize_anims(am);
	}

	am->asset_animations[am->animation_count++] = anim;
}

void asset_remove(AssetManager* am, Asset* asset) {
	_remove_item((void**)am->assets, &am->assets_count, asset);
}

void asset_animation_remove(AssetManager* am, AssetAnimation* anim) {
	_remove_item((void**)am->asset_animations, &am->animation_count, anim);
}

Asset* asset_get(AssetManager* am, const char* name) {
	for (int i = 0; i < am->assets_count; i++) {
		if (strcmp(am->assets[i]->name, name) == 0) {
			return am->assets[i];
		}
	}

	printf("[ERROR] - could not get asset for %s\n", name);

	return NULL;
}

AssetAnimation* asset_animation_get(AssetManager* am, const char* asset_name) {
	for (int i = 0; i < am->animation_count; i++) {
		if (strcmp(am->asset_animations[i]->asset->name, asset_name) == 0) {
			return am->asset_animations[i];
		}
	}

	printf("[ERROR] - could not get asset for %s\n", asset_name);

	return NULL;
}

void asset_manager_destroy(AssetManager* am) {
	// Free assets
	for (int i = 0; i < am->assets_count; i++) {
		UnloadTexture(am->assets[i]->texture);
		free(am->assets[i]);
	}
	free(am->assets);

	// Free animations
	for (int i = 0; i < am->animation_count; i++) {
		free(am->asset_animations[i]);
	}
	free(am->asset_animations);

	// Reset counts and capacities
	am->assets_count = 0;
	am->assets_capacity = 0;
	am->animation_count = 0;
	am->animation_capacity = 0;
}

void asset_destroy(Asset* a) {
	UnloadTexture(a->texture);
	free(a->name);
	free(a->path);
	free(a);
}

void asset_animation_destroy(AssetAnimation* a) {
	free(a);
}
