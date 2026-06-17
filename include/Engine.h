#pragma once   // means: only include this file once

class Engine {
private:
    double rpm;
    double maxRPM;
    double horsepower;
    double temperature;
    double throttle;

public:
    // Constructor: sets up the engine with its specs
    Engine(double maxRPM, double horsepower);

    void increaseThrottle(double amount);
    void decreaseThrottle(double amount);
    void updateRPM(double dt);           // dt = time step in seconds
    void updateTemperature(double dt);

    // Getters
    double getRPM()         const;
    void   setRPM(double newRPM);
    double getTemperature() const;
    double getHorsepower()  const;
    double getThrottle()    const;
    double getTorque()      const;
    bool   isOverheating()  const { return temperature >= 240.0; }
};