package mge

import rl "github.com/gen2brain/raylib-go/raylib"

// DefaultFontSize the default size of fonts
var DefaultFontSize = 12

// TextComponent a component wich has text
type TextComponent struct {
	Component
	ColorComponent
	FontSize int
	Text     string
}

// SetText sets the text of a text componenet
func (l *TextComponent) SetText(s string) {
	l.Text = s
}

// SetSize sets the width and height a text componenet
func (l *TextComponent) SetSize(w int, h int) {
	l.Width = w
	l.Height = h
}

// SetFontSize sets the size of the font
func (l *TextComponent) SetFontSize(fs int) {
	l.FontSize = fs
	l.SetSize(int(rl.MeasureText(l.Text, int32(l.FontSize))), l.Height)
}
