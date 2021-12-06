package mge

import rl "github.com/gen2brain/raylib-go/raylib"

// Window holds info about the program window
type Window struct {
	Width  int
	Height int
	Title  string
	FPS    int
}

// New creates a new Window instance
func (w *Window) New() {
	rl.InitWindow(int32(w.Width), int32(w.Height), w.Title)
	rl.SetTargetFPS(int32(w.FPS))
}
