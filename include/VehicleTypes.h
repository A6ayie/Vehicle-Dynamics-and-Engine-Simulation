#pragma once
#include "Vehicle.h"

class SportsCar : public Vehicle {
public:
    SportsCar() : Vehicle(2800.0, 9000.0, 1000.0, 12.0) {}
};

class Truck : public Vehicle {
public:
    Truck() : Vehicle(8000.0, 4500.0, 350.0, 40.0) {}
};

class EconomyCar : public Vehicle {
public:
    EconomyCar() : Vehicle(2400.0, 6500.0, 130.0, 10.0) {}
};