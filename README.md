# Vehicle Dynamics & Engine Simulation System

A real-time vehicle physics simulator built in C++ featuring a full engine model,
6-speed manual transmission, and an interactive racing-style visual interface.

## Features

- **Engine simulation** — Bell-curve torque model, RPM response, overheating system
- **6-speed transmission** — Realistic gear ratios with drivetrain efficiency  
- **Fuel system** — Consumption rate scales with RPM
- **3 vehicle types** — Sports Car (1000hp), Truck (350hp), Economy Car (130hp)
- **Perspective road** — Scrolling lane markings that speed up with vehicle velocity
- **Circular HUD gauges** — Live speedometer and tachometer driven by the physics engine
- **Warnings** — Overheating and redline alerts when pushing the car to limits

## Build & Run

### Requirements
- macOS with Homebrew
- SFML 3 — `brew install sfml`
- g++ with C++17 support

### Terminal simulation
```
make run
```

### Visual interface
```
make run-visual
```

## Controls
| Key | Action       |
|-----|--------------|
| W   | Accelerate   |
| S   | Brake        |
| E   | Shift up     |
| C   | Shift down   |
| X   | Quit         |
## Tech Stack
- **C++17** — OOP with classes, inheritance, smart pointers
- **SFML 3** — Graphics, window management, real-time input
## Project Structure
```
src/
  Engine.cpp        — Torque curve, RPM simulation, temperature
  Transmission.cpp  — Gear ratios, wheel force calculation
  FuelTank.cpp      — Fuel consumption and tracking
  Vehicle.cpp       — Physics update loop combining all systems
  main.cpp          — Terminal-based simulation
  main_visual.cpp   — SFML racing-style visual interface
include/
  VehicleTypes.h    — SportsCar, Truck, EconomyCar via inheritance
```

## Author
Debbie — Computer Science, Wesleyan University