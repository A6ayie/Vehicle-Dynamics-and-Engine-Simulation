#pragma once
#include "Vehicle.h"

// ─── Sports Cars ─────────────────────────────────────────────────────────────
class SportsCar : public Vehicle {
public:
    SportsCar()   : Vehicle(2800.0, 9000.0, 1000.0, 12.0) {}
};

class Ferrari488 : public Vehicle {
public:
    Ferrari488()  : Vehicle(1500.0, 8000.0,  660.0, 78.0) {}
};

class Porsche911 : public Vehicle {
public:
    Porsche911()  : Vehicle(1640.0, 7200.0,  640.0, 67.0) {}
};

class BMWM3 : public Vehicle {
public:
    BMWM3()       : Vehicle(1730.0, 7200.0,  503.0, 59.0) {}
};

// ─── Trucks ──────────────────────────────────────────────────────────────────
class Truck : public Vehicle {
public:
    Truck()       : Vehicle(8000.0, 4500.0,  350.0, 40.0) {}
};

class FordF150 : public Vehicle {
public:
    FordF150()    : Vehicle(2400.0, 5000.0,  450.0, 135.0) {}
};

// ─── Economy ─────────────────────────────────────────────────────────────────
class EconomyCar : public Vehicle {
public:
    EconomyCar()  : Vehicle(2400.0, 6500.0,  130.0, 10.0) {}
};

class ToyotaCorolla : public Vehicle {
public:
    ToyotaCorolla() : Vehicle(1350.0, 6500.0, 169.0, 50.0) {}
};

class HondaCivic : public Vehicle {
public:
    HondaCivic()  : Vehicle(1300.0, 6500.0,  158.0, 46.0) {}
};
