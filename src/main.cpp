#include <iostream>
#include "Engine.h"
#include "Transmission.h"

int main() {
    // Create an engine: 7000 RPM max, 300 horsepower
    Engine engine(7000.0, 300.0);

    std::cout << "Engine started\n";
    std::cout << "RPM: " << engine.getRPM() << "\n";
    std::cout << "Temp: " << engine.getTemperature() << " F\n";

    // Apply full throttle and simulate 3 seconds
    engine.increaseThrottle(1.0);

    for (int i = 0; i < 3; i++) {
        engine.updateRPM(1.0);
        engine.updateTemperature(1.0);
        std::cout << "\n--- Second " << i + 1 << " ---\n";
        std::cout << "RPM:      " << engine.getRPM() << "\n";
        std::cout << "Temp:     " << engine.getTemperature() << " F\n";
        std::cout << "Throttle: " << engine.getThrottle() * 100 << "%\n";
    }

    Transmission transmission;
    std::cout << "\nGear: " << transmission.getGear() << "\n";
    std::cout << "Ratio: " << transmission.getGearRatio() << "\n";

    transmission.shiftUp();
    transmission.shiftUp();
    std::cout << "Gear: " << transmission.getGear() << "\n";
    std::cout << "Ratio: " << transmission.getGearRatio() << "\n";

    return 0;
}