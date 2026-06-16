#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "Vehicle.h"
#include "Dashboard.h"

void enableRawMode(struct termios& original) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, &original);
    raw = original;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN]  = 1;  // wait for exactly 1 keypress
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disableRawMode(struct termios& original) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

int main() {
    Vehicle car;
    Dashboard dashboard(car);

    struct termios original;
    enableRawMode(original);

    bool running = true;

    std::cout << "\033[2J\033[H";
    dashboard.display();
    std::cout << "\n[W] Gas  [S] Brake  [E] Shift Up  [Q] Shift Down  [C] Coast  [X] Quit\n";

    while (running) {
        char c;
        read(STDIN_FILENO, &c, 1);  // waits here until you press a key

        switch (c) {
            case 'w': case 'W': car.accelerate(1.0); break;
            case 's': case 'S': car.brake(1.0);       break;
            case 'e': case 'E': car.shiftUp();         break;
            case 'q': case 'Q': car.shiftDown();       break;
            case 'c': case 'C': car.liftOff();         break;
            case 'x': case 'X': running = false;       break;
            default:  break;
        }

        if (running) {
            car.update(0.5);
            std::cout << "\033[2J\033[H";
            dashboard.display();
            std::cout << "\n[W] Gas  [S] Brake  [E] Shift Up  [Q] Shift Down  [C] Coast  [X] Quit\n";
        }
    }

    disableRawMode(original);
    std::cout << "\nSimulation ended.\n";
    return 0;
}