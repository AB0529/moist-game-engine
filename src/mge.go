package mge

import rl "github.com/gen2brain/raylib-go/raylib"

// MGE struct holding info about everything
type _MGE struct {
	// Textures map of all loaded textures
	Textures *Textures
	// Window the program window
	Window *Window
}

var (
	Engine = NewMGE()
)

// NewMGE initalizes the engine
func NewMGE() *_MGE {
	m := &_MGE{
		Textures: &Textures{
			DefaultImage:   DefaultImage,
			DefaultTexture: DefaultTexture,
			Lookup:         map[string]*rl.Texture2D{},
		},
	}

	return m
}

// NewWindow initalizes a new program window
func (m *_MGE) NewWindow(width int, height int, title string, FPS int) {
	window := &Window{
		Width:  width,
		Height: height,
		Title:  title,
		FPS:    FPS,
	}

	m.Window = window
	window.New()
}

// Close closes everything cleanly
func (m *_MGE) Close() {
	m.Textures.Unload()
	rl.CloseWindow()
}
