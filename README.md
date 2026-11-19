# Tornado Chasing

A 3D storm chasing simulator built with **Unreal Engine 5**, combining
C++ systems with Blueprint-based gameplay development.

## Current prototype

- Blueprint-ready starter character with on-foot movement.
- First-person / third-person camera toggle (V key).
- Physics-driven pickup pawn with throttle (W/S), steering (A/D),
  and chase camera.
- Exposed driving parameters for tuning in a Blueprint child.

## Vehicle setup

Create a Blueprint child of `AChaseTruck` and assign a pickup-truck
Static Mesh to `TruckBody`. Ensure the mesh has a suitable simple
collision shape. Place the Blueprint in a test level and possess it
from a Player Controller to test driving.

The current controller is a physics prototype, not a full Chaos Vehicle
suspension/wheel simulation. Enter/exit interaction is the next step.

## Development

C++ provides reusable gameplay foundations, while Blueprints are used
to prototype and extend gameplay in the Unreal Editor.

See [Docs/ROADMAP.md](Docs/ROADMAP.md) for planned milestones.

> The Unreal Engine editor is required to generate project files,
> compile, and run the game.
