package mge

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

// Element interface for a component
type Element interface {
	Draw()
	Update()
	Delete()
	SetPos(int, int)
	SetSize(int, int)
	GetPos() *rl.Vector2
	GetWidth() int
	GetHeight() int
	Contains(int, int) bool
}

// Component a entity or UI component
type Component struct {
	// Pos the XY coords
	Pos rl.Vector2
	// Width the width
	Width int
	// Height the height
	Height int
}

// SetPos sets the position of the element
func (c *Component) SetPos(x int, y int) {
	c.Pos.X = float32(x)
	c.Pos.Y = float32(y)
}

// SetSize sets the width and height of the element
func (c *Component) SetSize(w int, h int) {
	c.Width = w
	c.Height = h
}

// GetWidth gets the width of the element
func (c *Component) GetWidth() int {
	return c.Width
}

// GetHeight gets the height of the element
func (c *Component) GetHeight() int {
	return c.Height
}

// GetPos gets the position of the element
func (c *Component) GetPos() *rl.Vector2 {
	return &c.Pos
}

// Contains checks if coords are inside the element
func (c *Component) Contains(x int, y int) bool {
	return (int(c.Pos.X) < x && float32(x) < c.Pos.X+float32(c.Width) &&
		int(c.Pos.Y) < y && float32(y) < c.Pos.Y+float32(c.Height))
}

// GetType gets the type of the component
func GetTypeOfElement(e Element) string {
	switch e.(type) {
	case *Label:
		return "label"
		// return e.(*Label)
	case *Button:
		return "button"
		// return e.(*Button)
	case *Grid:
		return "grid"
		// return e.(*Grid)
	}

	return ""
}

// Delete deletes a component
func (c *Component) Delete() {
	c = nil
}
