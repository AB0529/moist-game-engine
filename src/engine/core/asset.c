#include "asset.h"

#include <raylib.h>
#include <stdlib.h>

Asset* asset_init(char* name, char* path, Vector2 scale) {
	Asset* a = malloc(sizeof(Asset));

	a->path = path;
	a->name = name;
	a->scale = scale;
	a->rotation = 0;
	a->texture = LoadTexture(path);

	if (a->texture.id == 0) {
		free(a);
		return NULL;
	}

	return a;
}
