#pragma once
#include "Engine.h"
#include "Transmission.h"
#include "FuelTank.h"

class Vehicle {
private:
    Engine       engine;
    Transmission transmission;
    FuelTank     fuelTank;
    double       speed;
    double       mass;

public:
    Vehicle(double mass, double maxRPM, double horsepower, double fuelCapacity);

    void accelerate(double amount);
    void brake(double amount);
    void liftOff();
    void shiftUp();
    void shiftDown();
    void update(double dt);

    double getSpeed()          const;
    double getRPM()            const;
    double getTemperature()    const;
    double getFuelPercentage() const;
    double getThrottle()       const;
    int    getGear()           const;
    bool   isRunning()         const;
    bool   isWheelspinning()   const;
};
