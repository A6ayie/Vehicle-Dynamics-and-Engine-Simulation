#pragma once

class Transmission {
private:
    int currentGear;
    int maxGears;
    double gearRatios[6];

public:
    Transmission();

    void shiftUp();
    void shiftDown();

    int    getGear()      const;
    double getGearRatio() const;
};