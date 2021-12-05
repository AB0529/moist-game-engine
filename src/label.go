package mge

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

// Label text label for UI element
type Label struct {
	Component
	Text string
}

// NewLabel creates a new label component
func NewLabel(s string) *Label {
	return &Label{
		Text: s,
	}
}

func (l *Label) Update() {}

// Copy copies the label
func (l *Label) Copy() Label {
	cpy := l

	return *cpy
}

// GetPos returns the position vector
func (l *Label) GetPos() rl.Vector2 {
	return l.Pos
}

// GetWidth returns the width of the label
func (l *Label) GetWidth() int32 {
	return rl.MeasureText(l.Text, l.FontSize)
}

// GetHeight returns the height of the label
func (l *Label) GetHeight() int32 {
	return l.FontSize
}

// SetText sets the text of the label
func (l *Label) SetText(s string) {
	l.Text = s
}

// SetSize sets the width and height of the label
func (l *Label) SetSize(w int32, h int32) {
	l.Width = w
	l.Height = h
}

// SetFontSize sets the size of the font
func (l *Label) SetFontSize(fs int32) {
	l.FontSize = fs
}

// Draw drwas the label on the screen
func (l *Label) Draw() {
	rl.DrawText(l.Text, int32(l.Pos.X), int32(l.Pos.Y), l.FontSize, l.FG)
}
