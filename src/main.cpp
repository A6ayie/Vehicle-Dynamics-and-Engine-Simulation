#include <iostream>
#include "Vehicle.h"

int main() {
    Vehicle car;

    car.accelerate(1.0);   // full throttle

    for (int i = 0; i < 5; i++) {
        car.update(1.0);
        std::cout << "--- Second " << i + 1 << " ---\n";
        std::cout << "Speed: " << car.getSpeed()          << " mph\n";
        std::cout << "RPM:   " << car.getRPM()            << "\n";
        std::cout << "Gear:  " << car.getGear()           << "\n";
        std::cout << "Fuel:  " << car.getFuelPercentage() << "%\n\n";
    }

    return 0;
}