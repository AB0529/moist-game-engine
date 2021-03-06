package mge

import rl "github.com/gen2brain/raylib-go/raylib"

// Label a text component
type Label struct {
	TextComponent
}

// NewLabel creates a new label component
func NewLabel(text string) *Label {
	l := &Label{
		TextComponent: TextComponent{
			FontSize: DefaultFontSize,
			Text:     text,
		},
	}

	l.Width = int(rl.MeasureText(l.Text, int32(l.FontSize)))
	l.Height = l.FontSize

	return l
}

// GetWidth gets the width of the label
func (l *Label) GetWidth() int {
	return l.Width
}

// GetHeight gets the height of the label
func (l *Label) GetHeight() int {
	return l.Height
}

// Copy copies the label
func (l *Label) Copy() Label {
	cpy := *l

	return cpy
}

// Update balnk update for now
func (l *Label) Update() {}

// Draw drwas the label on the screen
func (l *Label) Draw() {
	rl.DrawText(l.Text, int32(l.Component.GetPos().X), int32(l.Component.GetPos().Y), int32(l.FontSize), *l.GetFG())
}
