package main

import (
	mge "AB0529/mge/src"
	"fmt"

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
		mge.Engine.Window.Width/2-int(rl.MeasureText(logo.Text, int32(logo.FontSize))/2),
		int(logo.FontSize)/2,
	)
	// Add elements to the scene
	menu.AddElement(logo)

	// Create grid
	menuGrid := mge.NewGrid(3, 4)
	menuGrid.SetPos(menuGrid.Width+5*menuGrid.Cols/2*menuGrid.Cols, logo.FontSize+20)
	// Create buttons for the grid
	// Start btn
	startBtn := mge.NewButton("Start")
	startBtn.Component.SetPos(512, 512)
	startBtn.SetColor(rl.White, rl.Lime)
	startBtn.SetFontSize(32)
	startBtn.SetSizeOffText()

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
	startBtn.SetSizeOffText()
	exitBtn := startBtn.Copy()
	exitBtn.SetText("Eaxidfdt")
	exitBtn.SetColor(rl.White, rl.Red)
	exitBtn.SetOnClick(func(b *mge.Button) {
		menu.StopScene()
	})
	startBtn.SetSizeOffText()

	// Add buttons to grid
	menuGrid.AddElement(startBtn, 0, 0)
	fmt.Println("Start BTN ", startBtn.GetWidth())
	menuGrid.AddElement(&stopBtn, 1, 0)
	fmt.Println("Stop BTN ", stopBtn.GetWidth())
	menuGrid.AddElement(&exitBtn, 2, 0)
	fmt.Println("Exit BTN ", exitBtn.GetWidth())

	// Create some entities
	player := mge.NewEntity("assets/cube.png", 1, 1)
	player.SetPos(mge.CenterX(), mge.CenterY())
	menu.AddEntity(player)

	// Add grid to menu scene
	menu.AddElement(menuGrid)

	fmt.Println(menuGrid.Elements)

	// Start scenes
	mge.StartScenes()

	mge.Engine.Close()
}

func MenuDraw(s *mge.Scene) {
	player := s.Entities[0]

	player.Draw()

	s.SetColorBackground(rl.DarkPurple)
}

func MenuUpdate(s *mge.Scene) {
	player := s.Entities[0]

	player.FollowUserInput(20)
	player.MoveBackOnScreen(1)

	if rl.IsKeyPressed(rl.KeyEscape) {
		s.StopScene()
	}
}
