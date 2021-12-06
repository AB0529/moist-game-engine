package main

import (
	mge "AB0529/mge/src"

	rl "github.com/gen2brain/raylib-go/raylib"
)

func main() {
	mge.Engine.NewWindow(1000, 800, "Gamer", 30)

	// Create menu scene
	menu := mge.NewScene("Menu", MenuDraw, MenuUpdate)
	// Add logo to menu
	logo := mge.NewLabel("Moist Game Engine")
	logo.SetColor(rl.Purple, rl.Blank)
	logo.SetFontSize(32)
	logo.SetPos(
		mge.Engine.Window.Width/2-int(rl.MeasureText(logo.Text, logo.FontSize)/2),
		int(logo.FontSize)/2,
	)
	// Add elements to the scene
	menu.AddElement(logo)

	// Create grid
	menuGrid := mge.NewGrid(3, 4, 128, 32, 5)
	menuGrid.SetPos((int(menuGrid.Width+5*int32(menuGrid.Cols))/2)*menuGrid.Cols, int(logo.FontSize)+20)
	// Create buttons for the grid
	// Start btn
	startBtn := mge.NewButton("Start", func(b *mge.Button) {})
	startBtn.SetColor(rl.White, rl.Lime)
	startBtn.SetFontSize(32)
	stopBtn := startBtn.Copy()
	stopBtn.SetText("New")
	stopBtn.SetColor(rl.White, rl.Orange)
	stopBtn.SetOnClick(func(b *mge.Button) {
		// Swap colors
		if b.BG == rl.Orange {
			b.SetColor(rl.White, rl.Pink)
		} else {
			b.SetColor(rl.White, rl.Orange)
		}

	})
	exitBtn := startBtn.Copy()
	exitBtn.SetText("Exit")
	exitBtn.SetColor(rl.White, rl.Red)
	exitBtn.SetOnClick(func(b *mge.Button) {
		menu.StopScene()
	})

	// Add buttons to grid
	menuGrid.AddElement(startBtn, 0, 0)
	menuGrid.AddElement(&stopBtn, 0, 1)
	menuGrid.AddElement(&exitBtn, 0, 2)

	// Add grid to menu scene
	menu.AddGrid(menuGrid)
	// Start scenes
	mge.StartScenes()

	mge.Engine.Close()
}

func MenuDraw(s *mge.Scene) {
	s.SetColorBackground(rl.DarkPurple)
}

func MenuUpdate(s *mge.Scene) {
	if rl.IsKeyPressed(rl.KeyEscape) {
		s.StopScene()
	}
}
