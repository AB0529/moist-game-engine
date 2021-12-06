package mge

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

// Animation handles an animation based on sprite and tile size
type Animaton struct {
	// Texture sprite texture
	Texture *rl.Texture2D
	// Height subsection height in units
	Height int32
	// Width subsection width in units
	Width int32
	// CI current height index
	CI int32
	// CJ current width index
	CJ int32
}

// NewAnimation creates a new animation
func NewAnimation(path string, w int32, h int32) *Animaton {
	return &Animaton{
		Texture: Engine.Textures.Get(path),
		Height:  h,
		Width:   w,
		CI:      0,
		CJ:      0,
	}
}

// Copy copies the animation
func (a *Animaton) Copy() *Animaton {
	copy := *a
	return &copy
}

// Update updates the sprite indexies
func (a *Animaton) Update(row int32, min int32, max int32) {
	a.CJ += 2
	a.CI = row

	if a.CJ >= a.Width {
		a.CJ = 0
		a.CI++
	}

	if a.CI >= a.Height {
		a.CI = 0
	}

	if a.CJ > max {
		a.CJ = min
	}

	if a.CJ < min {
		a.CJ = min
	}
}

// Draw draws the animation sprite
func (a *Animaton) Draw(pos rl.Vector2, scale float32, rotation float32) {
	rl.DrawTexturePro(
		*a.Texture,
		rl.Rectangle{
			X:      float32(a.Texture.Width / a.Width * a.CJ),
			Y:      float32(a.Texture.Height / a.Height * a.CI),
			Width:  float32(a.Texture.Width / a.Width),
			Height: float32(a.Texture.Height / a.Height),
		},
		rl.Rectangle{
			X:      pos.X,
			Y:      pos.Y,
			Width:  float32(a.Texture.Width/a.Width) * scale,
			Height: float32(a.Texture.Height/a.Height) * scale,
		},
		rl.Vector2{X: 0, Y: 0},
		rotation,
		rl.White,
	)
}

// Reset resets the animation indexies
func (a *Animaton) Reset() {
	a.CI = 0
	a.CJ = 0
}

// GetWidth gets the width of the tile
func (a *Animaton) GetWidth() int32 {
	return a.Texture.Width / a.Width
}

// GetHeight gets height of the tile
func (a *Animaton) GetHeight() int32 {
	return a.Texture.Height * a.Height
}
