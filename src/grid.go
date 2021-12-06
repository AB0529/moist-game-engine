package mge

var (
	DefaultGridPadding = 10
	DefaultGridMargin  = 10
)

// Grid aligns elements in grid
type Grid struct {
	Component
	// Rows the size of the rows
	Rows int
	// Cols the size of the collums
	Cols int
	// Margin the amount of space between elements
	Margin int
	// Padding the amount of padding between elements
	Padding int
	// Elements the actual grid containg the elements
	Elements [][]*Element
}

// NewGrid creates a new grid
func NewGrid(rows int, cols int) *Grid {
	// Create grid array
	var grid = make([][]*Element, rows)
	for i := range grid {
		grid[i] = make([]*Element, cols)
	}

	return &Grid{
		Rows:     rows,
		Cols:     cols,
		Padding:  DefaultGridPadding,
		Margin:   DefaultGridMargin,
		Elements: grid,
	}
}

// AddElement adds an element to the grid
func (g *Grid) AddElement(elem Element, r int, c int) {
	g.Elements[r][c] = &elem

	// for i, r := range g.Elements {
	// 	for j, c := range r {
	// 		// Make sure there's an empty spot
	// 		if c == nil {
	// 			g.Elements[i][j] = &elem
	// 			break
	// 		}
	// 	}
	// }
}

// Update update func
func (g *Grid) Update() {}

// Draw draws the grid and the elements in it
func (g *Grid) Draw() {
	// Don't draw if grid is empty
	if len(g.Elements) != 0 {
		// Get each element
		for i, r := range g.Elements {
			for _, c := range r {
				if c != nil {
					cc := *c

					w := cc.GetWidth()
					h := cc.GetHeight()

					x := (g.Margin + int(w)) * i
					y := (g.Padding + int(h))

					cc.SetPos(x+int(g.Pos.X), y+int(g.Pos.Y))

					cc.Update()
					cc.Draw()
				}
			}
		}
	}
}
