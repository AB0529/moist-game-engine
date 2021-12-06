package mge

import (
	"math"

	rl "github.com/gen2brain/raylib-go/raylib"
)

type ButtonCallback func(b *Button)

// DefaultButtonPadding the extra padding and margin around the button's text
var DefaultButtonPadding = 10
var DefaultButtonOnClickCallback = func(b *Button) {}

// Button button element
type Button struct {
	TextComponent
	ColorComponent
	Padding int
	OnClick ButtonCallback
}

// NewButton creates a new button component
func NewButton(text string) *Button {
	return &Button{
		TextComponent: TextComponent{
			FontSize: DefaultFontSize,
			Text:     text,
		},
		ColorComponent: ColorComponent{
			FG: DefaultFGColor,
			BG: DefaultBGColor,
		},
		Padding: DefaultButtonPadding,
		OnClick: DefaultButtonOnClickCallback,
	}
}

// Copy copies the button
func (b *Button) Copy() Button {
	cpy := *b

	return cpy
}

// SetOnClick sets the callback function
func (b *Button) SetOnClick(f ButtonCallback) {
	b.OnClick = f
}

// SetSizeOffText will determin the width and hieght based off the text
func (b *Button) SetSizeOffText() {
	l := rl.MeasureText(b.Text, int32(b.FontSize))

	b.Component.SetSize(int(l)+b.Padding, b.FontSize)
}

// Update updates button
func (b *Button) Update() {
	if b.Contains(int(rl.GetMouseX()), int(rl.GetMouseY())) && rl.IsMouseButtonReleased(rl.MouseLeftButton) {
		b.OnClick(b)
	}
}

// Draw draws the button on screen
func (b Button) Draw() {
	tmp := b.BG
	txt := b.FG

	// Increase shade of button if hovered over
	if b.Contains(int(rl.GetMouseX()), int(rl.GetMouseY())) {
		tmp.R = uint8(math.Min(255, float64(tmp.R)*1.2))
		tmp.G = uint8(math.Min(255, float64(tmp.G)*1.2))
		tmp.B = uint8(math.Min(255, float64(tmp.B)*1.2))
		// txt = b.BG
	}
	x := int32(b.Pos.X)
	y := int32(b.Pos.Y)
	w := int32(b.Component.Width)
	h := int32(b.Component.Height + b.Padding)
	b.Component.SetSize(int(w), int(h))

	rl.DrawRectangle(x, y, w, h, tmp)

	x = int32(b.Pos.X + (float32(b.Component.Width) / 2) - float32(rl.MeasureText(b.Text, int32(b.FontSize))/2))
	y = int32(b.Component.GetPos().Y) + int32(b.Component.GetHeight())/2 - int32(b.FontSize)/3

	rl.DrawText(
		b.Text,
		x,
		y-int32(b.Padding)+4,
		int32(b.FontSize),
		txt,
	)
}
