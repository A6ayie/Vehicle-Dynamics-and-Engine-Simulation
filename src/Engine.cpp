#include "Engine.h"
#include <cmath>
#include <algorithm>
#include <algorithm>   // gives us std::clamp (keeps a value between two limits)

Engine::Engine(double maxRPM, double horsepower)
    : rpm(800.0), maxRPM(maxRPM), horsepower(horsepower),
      temperature(180.0), throttle(0.0)
{}

//Throttle functions
void Engine::increaseThrottle(double amount) {
    throttle = std::clamp(throttle + amount, 0.0, 1.0);
}

void Engine::decreaseThrottle(double amount) {
    throttle = std::clamp(throttle - amount, 0.0, 1.0);
}

//RPM updates
void Engine::updateRPM(double dt) {
    double targetRPM = 800.0 + throttle * (maxRPM - 800.0);
    rpm += (targetRPM - rpm) * 3.0 * dt;
    rpm = std::clamp(rpm, 800.0, maxRPM);
}

//Temperature updates
void Engine::updateTemperature(double dt) {
    temperature += (rpm / maxRPM) * 5.0 * dt;
    temperature -= (temperature - 180.0) * 0.1 * dt;
    temperature = std::max(temperature, 180.0);
}

//Getters
double Engine::getRPM()         const { return rpm; }
void Engine::setRPM(double newRPM) { rpm = std::clamp(newRPM, 800.0, maxRPM); }
double Engine::getTemperature() const { return temperature; }
double Engine::getHorsepower()  const { return horsepower; }
double Engine::getTorque() const {
    double n = rpm / maxRPM;                          // ← no underscores
    double baseTorque = horsepower * (n / 0.4) * std::exp(1.0 - n / 0.4) * throttle;

    // Power loss above 240°F
    double tempPenalty = 1.0;
    if (temperature > 240.0) {                        // ← temperature, not temp_
        tempPenalty = 1.0 - (temperature - 240.0) / 100.0;
        if (tempPenalty < 0.0) tempPenalty = 0.0;
    }

    return baseTorque * tempPenalty;
}

double Engine::getThrottle() const { return throttle; } 