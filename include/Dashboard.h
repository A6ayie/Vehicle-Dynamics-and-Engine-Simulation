#pragma once
#include "Vehicle.h"

class Dashboard {
private:
    const Vehicle& vehicle;

public:
    Dashboard(const Vehicle& vehicle);
    void display() const;
};