# Vehicle Dynamics & Engine Simulation System

A real-time vehicle physics simulator built in C++. It models how real car engines
work — torque curves, gear ratios, aerodynamic drag, tyre friction — and visualises
everything in a live racing-style interface. The same physics concepts are used in
professional racing games.

---

## Features

### Physics Engine
- **Torque curve model** — bell-curve RPM-to-torque response like a real engine
- **6-speed manual transmission** — realistic gear ratios affecting top speed and acceleration
- **Aerodynamic drag** — F = ½ρCdAv² formula slows the car at high speed
- **Tyre friction / wheelspin** — low-grip launch at high throttle, especially in sports cars
- **RPM drop on gear shift** — RPM recalculates correctly when shifting up or down
- **Engine temperature** — rises with RPM, causes power loss if overheating
- **Fuel system** — burn rate scales with RPM, fuel gauge drains in real time

### Visual Interface
- **Perspective road** — scrolling lane markings that speed up with the car
- **Live circular gauges** — tachometer and speedometer driven by the physics engine
- **Speed telemetry graph** — rolling 200-sample chart of your speed history
- **HUD panel** — speed, RPM, gear, temperature, throttle bar, fuel bar
- **0–100 km/h timer** — starts automatically from a standstill, records your best time
- **Warnings** — REDLINE, OVERHEATING, WHEELSPIN alerts

### Audio
- **Menu music** — plays on the selection screen, fades to subtle background while driving
- **Engine sounds** — one per vehicle category, pitch changes live with RPM

### 9 Vehicles Across 3 Categories

| # | Vehicle | HP | Max RPM | Weight |
|---|---------|-----|---------|--------|
| 1 | Koenigsegg Agera | 1000 | 9000 | 2800 kg |
| 2 | Ferrari 488 GTB | 660 | 8000 | 1500 kg |
| 3 | Porsche 911 Turbo S | 640 | 7200 | 1640 kg |
| 4 | BMW M3 Competition | 503 | 7200 | 1730 kg |
| 5 | Freightliner M2 | 350 | 4500 | 8000 kg |
| 6 | Ford F-150 Raptor | 450 | 5000 | 2400 kg |
| 7 | Ford Fiesta | 130 | 6500 | 2400 kg |
| 8 | Toyota Corolla | 169 | 6500 | 1350 kg |
| 9 | Honda Civic | 158 | 6500 | 1300 kg |

---

## Physics Model

Each vehicle simulates the following forces:

- **Drive force** — derived from torque curve: `T(n) = HP × (n/n_peak) × e^(1 − n/n_peak) × throttle`
- **Aerodynamic drag** — `F_drag = 0.00045 × v²` (quadratic, speed-squared growth)
- **Rolling resistance** — `F_roll = 0.033 km/h/s` (constant tyre-road friction)
- **Tyre grip** — launch traction limited at high throttle + low speed

Each vehicle uses real published gear ratios. For example, the Ferrari 488 GTB uses its actual 7-speed DCT ratios: 3.09 · 2.13 · 1.56 · 1.17 · 0.91 · 0.73.

### Published vs Simulated 0–100 km/h Reference

The built-in 0–100 km/h timer can be compared against manufacturer figures:

| Vehicle | Published 0–100 | Notes |
|---------|----------------|-------|
| Koenigsegg Agera | 2.9 s | Hypercar reference |
| Ferrari 488 GTB | 3.0 s | Real DCT ratios used |
| Porsche 911 Turbo S | 2.7 s | PDK ratios used |
| BMW M3 Competition | 3.9 s | 8-speed auto ratios |
| Ford F-150 Raptor | 5.4 s | 10-speed auto (6 modelled) |
| Toyota Corolla | 8.5 s | 6-speed auto ratios |
| Honda Civic | 8.0 s | CVT approximated |
| Ford Fiesta (130hp) | 12–14 s | Economy baseline |
| Freightliner M2 | 35–40 s | Heavy commercial truck |

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

---

## Controls

| Key | Action |
|-----|--------|
| 1–9 | Select vehicle |
| W | Accelerate |
| S | Brake |
| E | Shift up |
| C | Shift down |
| R | Back to vehicle select |
| X | Quit |

---

## Tech Stack
- **C++17** — OOP with classes, inheritance, composition, smart pointers (`std::unique_ptr`)
- **SFML 3** — Graphics, window management, real-time input, audio

---

## Project Structure
```
src/
  Engine.cpp          — Torque curve, RPM simulation, temperature model
  Transmission.cpp    — Gear ratios, shift logic
  FuelTank.cpp        — Fuel consumption and tracking
  Vehicle.cpp         — Physics update loop combining all systems
  main.cpp            — Terminal-based simulation
  main_visual.cpp     — SFML racing-style visual interface
include/
  VehicleTypes.h      — 9 vehicles via inheritance (SportsCar, Ferrari488, Porsche911,
                        BMWM3, Truck, FordF150, EconomyCar, ToyotaCorolla, HondaCivic)
assets/
  car.png / truck.png / economy.png   — Vehicle sprites
  menu.mp3                            — Selection screen music
  engine_sports.mp3 / engine_truck.mp3 / engine_economy.mp3  — Engine sounds
```

---

## Author
Debbie — Computer Science, Wesleyan University
