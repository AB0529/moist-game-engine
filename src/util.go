package mge

import rl "github.com/gen2brain/raylib-go/raylib"

// Center grabs the center of the sceeen
func Center() *rl.Vector2 {
	x := float32(Engine.Window.Width / 2)
	y := float32(Engine.Window.Height / 2)

	return &rl.Vector2{X: x, Y: y}
}

// CenterX gets the center widtth
func CenterX() int {
	return Engine.Window.Width / 2
}

// CenterY gets the center height
func CenterY() int {
	return Engine.Window.Height / 2
}

// TopCenter gets the top center of the screen
func TopCenter() *rl.Vector2 {
	x := float32(CenterX())
	y := float32(0)

	return &rl.Vector2{X: x, Y: y}
}

// ValueInRange determins if a value is in range
func ValueInRange(v float32, min float32, max float32) bool {
	return (v >= min) && (v <= max)
}
