package mge

import rl "github.com/gen2brain/raylib-go/raylib"

var DefaultFGColor = rl.White
var DefaultBGColor = rl.Blank

// ColorComponent a component which has color
type ColorComponent struct {
	FG rl.Color
	BG rl.Color
}

// GetFG gets the FG color
func (c ColorComponent) GetFG() *rl.Color {
	return &c.FG
}

// GetBG gets the BG color
func (c *ColorComponent) GetBG() *rl.Color {
	return &c.BG
}

// GetColor gets both FG and BG colors
func (c *ColorComponent) GetColor() (*rl.Color, *rl.Color) {
	return &c.FG, &c.BG
}

// SetFG sets the FG color
func (c *ColorComponent) SetFG(fg rl.Color) {
	c.FG = fg
}

// SetFG sets the BG color
func (c *ColorComponent) SetBG(bg rl.Color) {
	c.BG = bg
}

// SetColor sets both the FG and BG color
func (c *ColorComponent) SetColor(fg rl.Color, bg rl.Color) {
	c.FG = fg
	c.BG = bg
}
