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
    void setRatios(const double ratios[6]);

    int    getGear()      const;
    double getGearRatio() const;
};