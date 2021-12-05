package mge

import (
	rl "github.com/gen2brain/raylib-go/raylib"
)

var Scenes = map[string]*Scene{}
var CurrentlyPlayingScene *Scene

// Scene bascially a "level"
type Scene struct {
	// Entites all entities in the scene
	Entities []*Entity
	// Components all UI componenets in the scene
	Components     []Element
	GridComponents []*GridComponent
	// EndScene true will end scene, false will continue the scene
	EndScene bool
	// DrawFunc the draw function
	DrawFunc func(s *Scene)
	// UpdateFunc the update function
	UpdateFunc func(s *Scene)
	// Name name of scene
	Name string
}

// NewScene will create a new scene
func NewScene(name string, draw func(s *Scene), update func(s *Scene)) *Scene {
	s := &Scene{
		Name:       name,
		DrawFunc:   draw,
		UpdateFunc: update,
	}

	Scenes[name] = s

	return s
}

// Next stops old scene and starts new scene
func (s *Scene) Next() {
	if len(Scenes) > 1 {
		// Delete old scene
		delete(Scenes, s.Name)
		// Stop current one
		s.StopScene()
	}
}

// StartScenes starts the scenes
func StartScenes() {
	for _, s := range Scenes {
		for !s.EndScene {
			CurrentlyPlayingScene = s

			s.UpdateFunc(s)
			rl.BeginDrawing()
			// Draw all components
			if len(s.Components) != 0 {
				for _, c := range s.Components {
					c.Draw()
				}
			}
			// Draw the grid
			if len(s.GridComponents) != 0 {
				for _, g := range s.GridComponents {
					for j, row := range g.Grid {
						for i, col := range row {
							// Draw each row
							if col != nil {
								x := (g.Margin+int(col.GetWidth()))*i + g.Margin
								y := (g.Margin+int(col.GetHeight()))*j + g.Margin
								col.SetPos(x+int(g.Pos.X), y+int(g.Pos.Y))
								col.SetSize(g.Width, g.Height)
								col.Draw()
								col.Update()
							}
						}
					}
				}
			}

			s.DrawFunc(s)
			rl.EndDrawing()
		}
	}
}

// StopScene will stop the scene
func (s *Scene) StopScene() {
	CurrentlyPlayingScene = nil
	s.EndScene = true

	// Remove everything from memeory when scene ends
	// Remove all components
	for _, e := range s.Components {
		e.Delete()
	}
	// Remove everything in grid
	for _, g := range s.GridComponents {
		for _, row := range g.Grid {
			for _, col := range row {
				// Delete each row
				if col != nil {
					col.Delete()
				}
			}
		}
	}
}

// AddEntity will add a entity to the scene
func (s *Scene) AddEntity(e *Entity) {
	s.Entities = append(s.Entities, e)
}

// AddElement will add an element to the scene
func (s *Scene) AddElement(e Element) {
	s.Components = append(s.Components, e)
}

// AddGrid adds the grid to the scene
func (s *Scene) AddGrid(g *GridComponent) {
	s.GridComponents = append(s.GridComponents, g)
}

// SetColorBackground sets the scene background to a color
func (s *Scene) SetColorBackground(color rl.Color) {
	rl.ClearBackground(color)
}

// SetImageBackground sets the scene background to a image
func (s *Scene) SetImageBackground(path string) {
	// Load the texutre
	t := Engine.Textures.Get(path)
	t.Height = int32(Engine.Window.Height)
	t.Width = int32(Engine.Window.Width)
	rl.DrawTexture(*t, 0, 0, rl.White)
}
