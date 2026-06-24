#include "Transmission.h"
#include <iostream>

Transmission::Transmission() : currentGear(1), maxGears(6) {
    gearRatios[0] = 3.67;
    gearRatios[1] = 2.10;
    gearRatios[2] = 1.36;
    gearRatios[3] = 1.01;
    gearRatios[4] = 0.82;
    gearRatios[5] = 0.65;
}

//Shifting
void Transmission::shiftUp() {
    if (currentGear < maxGears) {
        currentGear++;
        std::cout << "Shifted up to gear " << currentGear << "\n";
    } else {
        std::cout << "Already in highest gear\n";
    }
}

void Transmission::shiftDown() {
    if (currentGear > 1) {
        currentGear--;
        std::cout << "Shifted down to gear " << currentGear << "\n";
    } else {
        std::cout << "Already in lowest gear\n";
    }
}

void Transmission::setRatios(const double ratios[6]) {
    for (int i = 0; i < 6; i++)
        gearRatios[i] = ratios[i];
}

//Getters
int Transmission::getGear() const {
    return currentGear;
}

double Transmission::getGearRatio() const {
    return gearRatios[currentGear - 1];
}