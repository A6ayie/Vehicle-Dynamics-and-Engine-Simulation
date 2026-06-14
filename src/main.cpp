#include <iostream>
#include "Vehicle.h"
#include "Dashboard.h"

int main() {
    Vehicle car;
    Dashboard dashboard(car);

    car.accelerate(1.0);

    for (int i = 0; i < 5; i++) {
        car.update(1.0);
        dashboard.display();
    }

    return 0;
}