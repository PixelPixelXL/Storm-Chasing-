# Development roadmap

## Prototype 0.1 — Foundation

- [x] Create the Unreal Engine 5 project structure.
- [x] Set up a C++ game module that can be extended with Blueprints.
- [x] Add a starter character with first-person and third-person cameras.
- [x] Map the V key to switch camera views.
- [x] Add on-foot movement, mouse look, and jumping.
- [x] Add a physics-driven pickup pawn with throttle, steering, and chase camera.
- [ ] Create a Blueprint truck and assign a suitable vehicle mesh and collision.
- [ ] Add enter/exit interaction between the character and truck.
- [ ] Generate project files and compile in the selected Unreal Engine 5 installation.
- [ ] Create a small test level.
- [ ] Add a simple tornado actor for visual testing.

## Later versions

- [ ] Rural map with roads and landmarks.
- [ ] Rain, clouds, wind and thunderstorm ambience.
- [ ] Improved tornado visuals and movement.
- [ ] Storm-chasing instruments and radar display.

## Development approach

Use C++ for reusable core systems and expose properties and functions to Blueprints. Build gameplay prototypes and visual behavior in the Unreal Editor wherever practical.

The first milestone is a small playable prototype, not a full weather simulation.
