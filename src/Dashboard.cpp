#include "Dashboard.h"
#include <iostream>
#include <iomanip>

Dashboard::Dashboard(const Vehicle& vehicle)
    : vehicle(vehicle)
{}

void Dashboard::display() const {
    std::cout << "\n===========================\n";
    std::cout << "        DASHBOARD          \n";
    std::cout << "===========================\n";
    std::cout << "Speed  : " << std::setw(6) << std::fixed << std::setprecision(1)
              << vehicle.getSpeed()          << " mph\n";
    std::cout << "RPM    : " << std::setw(6) << static_cast<int>(vehicle.getRPM())    << "\n";
    std::cout << "Gear   : " << std::setw(6) << vehicle.getGear()                     << "\n";
    std::cout << "Temp   : " << std::setw(6) << std::setprecision(1)
              << vehicle.getTemperature()    << " F\n";
    std::cout << "Fuel   : " << std::setw(6) << std::setprecision(1)
              << vehicle.getFuelPercentage() << "%\n";
    std::cout << "Status : " << (vehicle.isRunning() ? "Running" : "STALLED") << "\n";
    std::cout << "===========================\n";
}