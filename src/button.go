package mge

import (
	"math"

	rl "github.com/gen2brain/raylib-go/raylib"
)

type ButtonCallback func(b *Button)

// Button button element
type Button struct {
	Component
	Text    string
	OnClick ButtonCallback
}

// NewButton creates a new button component
func NewButton(s string, callback ButtonCallback) *Button {
	return &Button{
		Text:    s,
		OnClick: callback,
	}
}

// GetPos returns the position vector
func (b *Button) GetPos() rl.Vector2 {
	return b.Pos
}

// GetWidth returns the width of the button
func (b *Button) GetWidth() int32 {
	return b.Width
}

// GetHeight returns the height of the button
func (b *Button) GetHeight() int32 {
	return b.Height
}

// SetText sets the text of the button
func (b *Button) SetText(s string) {
	b.Text = s
}

// SetSize sets the size of the element
func (b *Button) SetSize(w int32, h int32) {
	b.Width = w
	b.Height = h
}

// SetFontSize sets the size of the font
func (b *Button) SetFontSize(fs int32) {
	b.FontSize = fs
}

// SetSizeOffText will determin the width and hieght based off the text
func (b *Button) SetSizeOffText() {
	l := rl.MeasureText(b.Text, b.FontSize)

	b.SetSize(l+10, b.FontSize)
}

// Update updates button
func (b *Button) Update() {
	if b.Contians(rl.GetMousePosition()) && rl.IsMouseButtonReleased(rl.MouseLeftButton) {
		b.OnClick(b)
	}
}

// SetOnClick sets the callback function
func (b *Button) SetOnClick(f ButtonCallback) {
	b.OnClick = f
}

// Copy copies the button
func (b *Button) Copy() Button {
	cpy := b

	return *cpy
}

// Draw draws the button on screen
func (b Button) Draw() {
	tmp := b.BG
	txt := b.FG

	// Increase shade of button if hovered over
	if b.Contians(rl.GetMousePosition()) {
		tmp.R = uint8(math.Min(255, float64(tmp.R)*1.2))
		tmp.G = uint8(math.Min(255, float64(tmp.G)*1.2))
		tmp.B = uint8(math.Min(255, float64(tmp.B)*1.2))
		// txt = b.BG
	}
	rl.DrawRectangle(int32(b.Pos.X), int32(b.Pos.Y), b.Width, b.Height, tmp)
	rl.DrawText(
		b.Text,
		int32(b.Pos.X)+b.Width/2-rl.MeasureText(b.Text, b.FontSize)/2,
		int32(b.Pos.Y)+b.Height/2-int32(b.FontSize)/2,
		int32(b.FontSize),
		txt,
	)
}
