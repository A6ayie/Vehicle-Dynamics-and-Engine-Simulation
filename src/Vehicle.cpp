#include "Vehicle.h"
#include <iostream>

Vehicle::Vehicle()
    : engine(7000.0, 300.0), fuelTank(15.0), speed(0.0)
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

void Vehicle::shiftUp()   { transmission.shiftUp(); }
void Vehicle::shiftDown() { transmission.shiftDown(); }


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
                       * 120.0;
    speed += (targetSpeed - speed) * 2.0 * dt;
    if (speed < 0.0) speed = 0.0;

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