#pragma once
#include "Engine.h"
#include "Transmission.h"
#include "FuelTank.h"

class Vehicle {
private:
    Engine       engine;
    Transmission transmission;
    FuelTank     fuelTank;
    double       speed;    // mph

public:
    Vehicle();

    void accelerate(double amount);
    void brake(double amount);
    void liftOff();             // ← moved inside
    void shiftUp();
    void shiftDown();
    void update(double dt);

    double getSpeed()          const;
    double getRPM()            const;
    double getTemperature()    const;
    double getFuelPercentage() const;
    double getThrottle()       const;  // ← moved inside
    int    getGear()           const;
    bool   isRunning()         const;
};
