#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle(double mass, double maxRPM, double horsepower, double fuelCapacity)
    : engine(maxRPM, horsepower), fuelTank(fuelCapacity), speed(0.0),
      mass(mass)
{}


//Controls
void Vehicle::accelerate(double amount) {
    engine.increaseThrottle(amount);
}

void Vehicle::brake(double amount) {
    engine.decreaseThrottle(amount);
    speed -= amount * 20.0;
    if (speed < 0.0) speed = 0.0;
}

void Vehicle::shiftUp() {
    double oldRatio = transmission.getGearRatio();
    transmission.shiftUp();
    double newRatio = transmission.getGearRatio();
    engine.setRPM(engine.getRPM() * (newRatio / oldRatio));
}

void Vehicle::shiftDown() {
    double oldRatio = transmission.getGearRatio();
    transmission.shiftDown();
    double newRatio = transmission.getGearRatio();
    engine.setRPM(engine.getRPM() * (newRatio / oldRatio));
}


//Update
void Vehicle::update(double dt) {
    if (fuelTank.isEmpty()) {
        engine.decreaseThrottle(1.0);
        std::cout << "Out of fuel!\n";
    }

    engine.updateRPM(dt);
    engine.updateTemperature(dt);

    // Speed from RPM + gear ratio
    // Lower gear ratio = higher top speed in that gear
    double targetSpeed = (engine.getRPM() / 7000.0)
                   * (0.65 / transmission.getGearRatio())
                   * 120.0
                   * engine.getThrottle();
    double accelerationFactor = (engine.getHorsepower() / 500.0) * (2800.0 / mass);
    speed += (targetSpeed - speed) * 0.5 * accelerationFactor * dt;
    if (speed < 0.0) speed = 0.0;
    speed -= 0.00045 * speed * speed * dt;

    // Fuel burn rate rises with RPM
    double burnRate = 0.0005 + (engine.getRPM() / 7000.0) * 0.003;
    fuelTank.consumeFuel(burnRate * dt);
}


//Getters
double Vehicle::getSpeed()          const { return speed; }
double Vehicle::getRPM()            const { return engine.getRPM(); }
double Vehicle::getTemperature()    const { return engine.getTemperature(); }
double Vehicle::getFuelPercentage() const { return fuelTank.getFuelPercentage(); }
int    Vehicle::getGear()           const { return transmission.getGear(); }
bool   Vehicle::isRunning()         const { return !fuelTank.isEmpty(); }

void Vehicle::liftOff() {
    engine.decreaseThrottle(0.05);
}

double Vehicle::getThrottle() const { return engine.getThrottle(); }