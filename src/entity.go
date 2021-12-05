package mge

import (
	"math"

	rl "github.com/gen2brain/raylib-go/raylib"
)

// EntityMovementFunc function which moves an entity
type EntityMovementFunc func(e *Entity, amount float32)

// EntityMovement movements of an entity
type EntityMovement struct {
	Amount float32
	Type   EntityMovementFunc
}

// Entity repersents an entity in the game
type Entity struct {
	// Pos 2D vector with coords
	Pos rl.Vector2
	// Roation angle of the entity
	Roation float32
	// Scale size of the entity
	Scale float32
	// Bobrate how much the entity animation moves
	Bobrate float32
	// Bobratedeleta delta time of bobrate
	Bobratedeleta float32
	// Animation the sprite animation of the entity
	Animaton *Animaton
	// Movements which movement commands to do
	Movements []EntityMovement
}

func newEntityMovement(amount float32, movement EntityMovementFunc) EntityMovement {
	return EntityMovement{
		Amount: amount,
		Type:   movement,
	}
}

func (e *EntityMovement) moveUpdate(entity *Entity) {
	e.Type(entity, e.Amount)
}

// NewEntityFromAnimation creates a new entity object from animation
func NewEntityFromAnimation(animation *Animaton) *Entity {
	return &Entity{
		Pos:           rl.Vector2{X: float32((rl.GetScreenWidth() / 2)), Y: float32((rl.GetScreenHeight() / 2))},
		Bobrate:       0.001,
		Bobratedeleta: 0,
		Roation:       0,
		Scale:         1,
		Animaton:      animation,
		Movements:     make([]EntityMovement, 0, 4),
	}
}

// NewEntity creates a new entity
func NewEntity(path string, width int32, height int32) *Entity {
	return NewEntityFromAnimation(NewAnimation(path, width, height))
}

// Copy copies the entity
func (e *Entity) Copy() *Entity {
	copy := *e
	e.Animaton = e.Animaton.Copy()
	return &copy
}

// Update updates the entity movement
func (e *Entity) Update() {
	for i := 0; i < len(e.Movements); i += 1 {
		e.Movements[i].moveUpdate(e)
	}

	if e.Bobratedeleta > 2*math.Pi {
		e.Bobratedeleta = 0
	}
}

// IsOffScreenLeft checks if the entity of on or off left side of screen
func (e *Entity) IsOffScreenLeft() bool {
	return e.Pos.X+float32(e.Animaton.GetWidth()) < 0
}

// IsOffScreenRight checks if the entity of on or off right side of screen
func (e *Entity) IsOffScreenRight() bool {
	return e.Pos.X > float32(Engine.Window.Width)
}

// IsOffScreenBottom checks if the entity of on or off bottom side of screen
func (e *Entity) IsOffScreenTop() bool {
	return e.Pos.Y < 0
}

// IsOffScreenTop checks if the entity of on or off top side of screen
func (e *Entity) IsOffScreenBottom() bool {
	return e.Pos.Y > float32(Engine.Window.Height)
}

// IsOffScreen checks if entity is on or off screen
func (e *Entity) IsOffScreen() bool {
	return e.IsOffScreenLeft() ||
		e.IsOffScreenRight() ||
		e.IsOffScreenBottom() ||
		e.IsOffScreenTop()
}

// Draw draws the entity on screen
func (e *Entity) Draw() {
	if !e.IsOffScreen() {
		e.Animaton.Draw(e.Pos, e.Scale, e.Roation)
	}
}

// AddMovement adds movement to the entity
func (e *Entity) AddMovement(t EntityMovementFunc, amount float32) {
	e.Movements = append(e.Movements, newEntityMovement(amount, t))
}

// ### MOVMENT FUNCTIONS ### //

func (entity *Entity) RotateClockwise(amount float32) {
	entity.Roation += amount
}

func (entity *Entity) RotateCounterClockwise(amount float32) {
	entity.Roation -= amount
}

func (entity *Entity) SetScale(amount float32) {
	if entity.IsOffScreen() {
		entity.Scale = 1
	} else {
		entity.Scale *= amount
	}
}

func (entity *Entity) TrackMouseVertical(amount float32) {
	y := float32(rl.GetMouseY())

	if entity.Pos.Y > y {
		entity.Pos.Y -= float32(math.Abs(float64(entity.Pos.Y-y))) / amount
	} else {
		entity.Pos.Y += float32(math.Abs(float64(entity.Pos.Y-y))) / amount
	}
}

func (entity *Entity) TrackMouseHorizontal(amount float32) {
	x := float32(rl.GetMouseX())

	if entity.Pos.X > x {
		entity.Pos.X -= float32(math.Abs(float64(entity.Pos.X-x))) / amount
	} else {
		entity.Pos.X += float32(math.Abs(float64(entity.Pos.X-x))) / amount
	}
}

func (entity *Entity) Left(amount float32) {
	entity.Pos.X -= amount
}

func (entity *Entity) Right(amount float32) {
	entity.Pos.X += amount
}

func (entity *Entity) Up(amount float32) {
	entity.Pos.Y -= amount
}

func (entity *Entity) Down(amount float32) {
	entity.Pos.Y += amount
}

func (entity *Entity) BobVertical(amount float32) {
	entity.Pos.Y += amount * float32(math.Sin(float64(entity.Bobratedeleta)))
	entity.Bobratedeleta += entity.Bobrate
}

func (entity *Entity) BobHorizontal(amount float32) {
	entity.Pos.X += amount * float32(math.Cos(float64(entity.Bobratedeleta)))
	entity.Bobratedeleta += entity.Bobrate
}

func (entity *Entity) LoopLeft(amount float32) {
	entity.Left(amount)
	if entity.IsOffScreen() {
		entity.Pos.X = float32(rl.GetScreenWidth())
	}
}

func (entity *Entity) LoopRight(amount float32) {
	entity.Right(amount)
	if entity.IsOffScreen() {
		entity.Pos.X = 0 - float32(entity.Animaton.GetWidth())
	}
}

func (entity *Entity) LoopUp(amount float32) {
	entity.Up(amount)
	if entity.IsOffScreen() {
		entity.Pos.Y = float32(rl.GetScreenHeight())
	}
}

func (entity *Entity) HLoopDown(amount float32) {
	entity.Down(amount)
	if entity.IsOffScreen() {
		entity.Pos.Y = 0 - float32(entity.Animaton.GetHeight())
	}
}

func (entity *Entity) FollowUserInput(amount float32) {
	if rl.IsKeyDown(rl.KeyLeft) {
		entity.Left(amount)
		entity.Animaton.Update(1, 0, 5)
	} else if rl.IsKeyDown(rl.KeyRight) {
		entity.Right(amount)
		entity.Animaton.Update(3, 0, 5)
	} else if rl.IsKeyDown(rl.KeyUp) {
		entity.Up(amount)
		entity.Animaton.Update(0, 0, 5)
	} else if rl.IsKeyDown(rl.KeyDown) {
		entity.Down(amount)
		entity.Animaton.Update(2, 0, 5)
	} else {
		entity.Animaton.Reset()
	}

}

func (entity *Entity) MoveBackOnScreen(amount float32) {
	if entity.IsOffScreenLeft() {
		entity.Pos.X = float32(entity.Animaton.GetWidth())
	}
	if entity.IsOffScreenRight() {
		entity.Pos.X = float32(Engine.Window.Width) - float32(entity.Animaton.GetWidth())
	}
	if entity.IsOffScreenTop() {
		entity.Pos.Y = float32(entity.Animaton.GetHeight())
	}
	if entity.IsOffScreenBottom() {
		entity.Pos.Y = float32(entity.Animaton.GetHeight())
	}
}
