#include "FuelTank.h"

FuelTank::FuelTank(double capacity)
    : fuelLevel(capacity), fuelCapacity(capacity)
{}

//Consumption and refuel
void FuelTank::consumeFuel(double amount) {
    fuelLevel -= amount;
    if (fuelLevel < 0.0) fuelLevel = 0.0;
}

void FuelTank::refuel(double amount) {
    fuelLevel += amount;
    if (fuelLevel > fuelCapacity) fuelLevel = fuelCapacity;
}


//Getters
double FuelTank::getFuelLevel() const {
    return fuelLevel;
}

double FuelTank::getFuelPercentage() const {
    return (fuelLevel / fuelCapacity) * 100.0;
}

bool FuelTank::isEmpty() const {
    return fuelLevel <= 0.0;
}