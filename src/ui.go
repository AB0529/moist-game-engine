package mge

import (
	"errors"

	rl "github.com/gen2brain/raylib-go/raylib"
)

var (
	ErrGridFull = errors.New("the current grid is full")
)

// Component the UI element
type Component struct {
	// Pos the XY coords
	Pos rl.Vector2
	// Width the width
	Width int32
	// Height the height
	Height int32
	// FontSize size of the font
	FontSize int32
	// FG the color of the foreground
	FG rl.Color
	// BG the color of the background
	BG rl.Color
	// AllowOverlap allows overlapping of elements
	// TODO: impliment this
	AllowOverlap bool
}

type Element interface {
	Draw()
	SetPos(x int, y int)
	GetPos() rl.Vector2
	GetWidth() int32
	GetHeight() int32
	SetSize(w int32, h int32)
	Update()
	Delete()
}

// GridComponent componenets can only be placed inside this grid
type GridComponent struct {
	// Rows number of rows
	Rows int
	// Cols number of cols
	Cols int
	// Width width of each cell
	Width int32
	// Height height of each cell
	Height int32
	// Position of the grid
	Pos rl.Vector2
	// Grid the grid
	Grid [][]Element
	// Margin the space to leave between items
	Margin int
}

// NewGrid creates a new grid component
func NewGrid(rows int, cols int, tileW int32, tileH int32, margin int) *GridComponent {
	var grid = make([][]Element, rows)
	for i := range grid {
		grid[i] = make([]Element, cols)
	}

	return &GridComponent{
		Rows:   rows,
		Cols:   cols,
		Width:  tileW,
		Height: tileH,
		Grid:   grid,
		Margin: margin,
	}
}

// AddButton adds a button to the grid
func (g *GridComponent) AddElement(e Element, i int, j int) {
	g.Grid[i][j] = e
}

// SetPos sets the grids position
func (g *GridComponent) SetPos(x int, y int) {
	g.Pos = rl.Vector2{
		X: float32(x),
		Y: float32(y),
	}
}

// Contains check if coords are inside component
func (c *Component) Contians(pos rl.Vector2) bool {
	x := pos.X
	y := pos.Y

	return (c.Pos.X < x && x < c.Pos.X+float32(c.Width) &&
		c.Pos.Y < y && y < c.Pos.Y+float32(c.Height))
}

// SetPos sets a position of a component
func (c *Component) SetPos(x int, y int) {
	c.Pos = rl.Vector2{
		X: float32(x),
		Y: float32(y),
	}
}

// SetColor sets the fg and bg of the element
func (c *Component) SetColor(fg rl.Color, bg rl.Color) {
	c.FG = fg
	c.BG = bg
}

// Delete will delete a component
func (c *Component) Delete() {
	c = nil
}
