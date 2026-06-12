#pragma once

class FuelTank {
private:
    double fuelLevel;     // current fuel in gallons
    double fuelCapacity;  // max fuel the tank holds

public:
    FuelTank(double capacity);

    void consumeFuel(double amount);
    void refuel(double amount);

    double getFuelLevel()      const;
    double getFuelPercentage() const;
    bool   isEmpty()           const;
};