#pragma once
#include "Vehicle.h"

// ─── Sports Cars ─────────────────────────────────────────────────────────────
class SportsCar : public Vehicle {
public:
    SportsCar() : Vehicle(2800.0, 9000.0, 1000.0, 12.0) {
        // Koenigsegg Agera — hypercar ratios (estimated)
        double r[] = {2.93, 2.08, 1.61, 1.27, 1.01, 0.78};
        setGearRatios(r);
    }
};

class Ferrari488 : public Vehicle {
public:
    Ferrari488() : Vehicle(1500.0, 8000.0, 660.0, 78.0) {
        // Ferrari 488 GTB 7-speed DCT (published)
        double r[] = {3.09, 2.13, 1.56, 1.17, 0.91, 0.73};
        setGearRatios(r);
    }
};

class Porsche911 : public Vehicle {
public:
    Porsche911() : Vehicle(1640.0, 7200.0, 640.0, 67.0) {
        // Porsche 911 Turbo S 7-speed PDK
        double r[] = {3.91, 2.29, 1.56, 1.16, 0.86, 0.67};
        setGearRatios(r);
    }
};

class BMWM3 : public Vehicle {
public:
    BMWM3() : Vehicle(1730.0, 7200.0, 503.0, 59.0) {
        // BMW M3 Competition 8-speed auto (first 6)
        double r[] = {4.71, 3.14, 2.11, 1.67, 1.29, 1.00};
        setGearRatios(r);
    }
};

// ─── Trucks ──────────────────────────────────────────────────────────────────
class Truck : public Vehicle {
public:
    Truck() : Vehicle(8000.0, 4500.0, 350.0, 40.0) {
        // Freightliner M2 Allison 6-speed automatic
        double r[] = {5.11, 2.81, 1.67, 1.25, 0.91, 0.70};
        setGearRatios(r);
    }
};

class FordF150 : public Vehicle {
public:
    FordF150() : Vehicle(2400.0, 5000.0, 450.0, 135.0) {
        // Ford F-150 Raptor 10-speed auto (first 6)
        double r[] = {4.69, 2.98, 2.14, 1.52, 1.27, 1.00};
        setGearRatios(r);
    }
};

// ─── Economy ─────────────────────────────────────────────────────────────────
class EconomyCar : public Vehicle {
public:
    EconomyCar() : Vehicle(2400.0, 6500.0, 130.0, 10.0) {
        // Ford Fiesta 6-speed automatic
        double r[] = {4.21, 2.62, 1.75, 1.28, 1.00, 0.80};
        setGearRatios(r);
    }
};

class ToyotaCorolla : public Vehicle {
public:
    ToyotaCorolla() : Vehicle(1350.0, 6500.0, 169.0, 50.0) {
        // Toyota Corolla 6-speed auto (published)
        double r[] = {4.22, 2.63, 1.75, 1.26, 0.98, 0.82};
        setGearRatios(r);
    }
};

class HondaCivic : public Vehicle {
public:
    HondaCivic() : Vehicle(1300.0, 6500.0, 158.0, 46.0) {
        // Honda Civic CVT approximated as 6-speed
        double r[] = {3.88, 2.35, 1.60, 1.18, 0.90, 0.74};
        setGearRatios(r);
    }
};
