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
func (g *Grid) AddElement(elem Element) {
	for i, r := range g.Elements {
		for j, c := range r {
			// Make sure there's an empty spot
			if c == nil {
				g.Elements[i][j] = &elem
				break
			}
		}
	}
}

// Update update func
func (g *Grid) Update() {}

// Draw draws the grid and the elements in it
func (g *Grid) Draw() {
	// Get each element
	for _, r := range g.Elements {
		for j, c := range r {
			if c != nil {
				cc := *c

				// x := ((g.Margin+int(cc.GetWidth()))*i + g.Margin) + int(g.Pos.X)
				// y := ((g.Padding+int(cc.GetHeight()))*j + g.Padding) + int(g.Pos.Y)
				x := (cc.GetWidth() * j) + g.Margin

				cc.SetPos(50, x)

				cc.Update()
				cc.Draw()
			}
		}
	}
}