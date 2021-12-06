package mge

import (
	"os"

	rl "github.com/gen2brain/raylib-go/raylib"
)

var (
	DefaultImage   *rl.Image    = rl.LoadImage("assets/missing.png")
	DefaultTexture rl.Texture2D = rl.LoadTextureFromImage(DefaultImage)
)

// Textures holds info about the game textures
type Textures struct {
	// DefaultImage holds the default image
	DefaultImage *rl.Image
	// DefaultTexture holds the default texture
	DefaultTexture rl.Texture2D
	// Lookup map which holds all textures
	Lookup map[string]*rl.Texture2D
}

// Get attempts to grab a texture from the lookup
func (t *Textures) Get(path string) *rl.Texture2D {
	// Return already loaded texture
	if v, ok := t.Lookup[path]; ok {
		return v
	}

	// Image doesn't exist, return default image
	if _, err := os.Stat(path); os.IsNotExist(err) {
		return &t.DefaultTexture
	}

	// Load the image and return it
	texture := rl.LoadTexture(path)
	t.Lookup[path] = &texture

	return &texture
}

// Unload unloads all textures from VRAM
func (t *Textures) Unload() {
	// Unload all from lookup
	for _, t := range t.Lookup {
		rl.UnloadTexture(*t)
	}

	// Unload defaults
	rl.UnloadTexture(t.DefaultTexture)
	rl.UnloadImage(t.DefaultImage)
}
