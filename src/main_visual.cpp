#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include "VehicleTypes.h"

const unsigned int W       = 800;
const unsigned int H       = 600;
const float        HORIZON = 280.f;

// ─────────────────────────────────────────────────────────────────────────────
//  SCENE  (sky, grass, road, scrolling lane markings)
// ─────────────────────────────────────────────────────────────────────────────
void drawScene(sf::RenderWindow& window, float laneOffset) {

    // Sky — two-tone: very dark at top, slightly lighter near horizon
    sf::RectangleShape skyTop({(float)W, HORIZON * 0.6f});
    skyTop.setFillColor(sf::Color(8, 14, 50));
    window.draw(skyTop);

    sf::RectangleShape skyLow({(float)W, HORIZON * 0.4f});
    skyLow.setPosition({0.f, HORIZON * 0.6f});
    skyLow.setFillColor(sf::Color(22, 55, 125));
    window.draw(skyLow);

    // Grass
    sf::RectangleShape grass({(float)W, H - HORIZON});
    grass.setPosition({0.f, HORIZON});
    grass.setFillColor(sf::Color(20, 92, 20));
    window.draw(grass);

    // Road trapezoid
    sf::ConvexShape road;
    road.setPointCount(4);
    road.setPoint(0, {340.f, HORIZON});
    road.setPoint(1, {460.f, HORIZON});
    road.setPoint(2, {750.f, (float)H});
    road.setPoint(3, { 50.f, (float)H});
    road.setFillColor(sf::Color(46, 48, 52));
    window.draw(road);

    // Road edge lines (thin white trapezoid strips)
    sf::ConvexShape leftEdge;
    leftEdge.setPointCount(4);
    leftEdge.setPoint(0, {338.f, HORIZON});
    leftEdge.setPoint(1, {343.f, HORIZON});
    leftEdge.setPoint(2, { 53.f, (float)H});
    leftEdge.setPoint(3, { 47.f, (float)H});
    leftEdge.setFillColor(sf::Color(230, 230, 230, 200));
    window.draw(leftEdge);

    sf::ConvexShape rightEdge;
    rightEdge.setPointCount(4);
    rightEdge.setPoint(0, {457.f, HORIZON});
    rightEdge.setPoint(1, {462.f, HORIZON});
    rightEdge.setPoint(2, {753.f, (float)H});
    rightEdge.setPoint(3, {747.f, (float)H});
    rightEdge.setFillColor(sf::Color(230, 230, 230, 200));
    window.draw(rightEdge);

    // ── Perspective-scrolling center lane dashes ──────────────────────────────
    // laneOffset (0→1) increases with vehicle speed — faster = faster scroll
    // p*p warp bunches dashes near horizon (correct perspective feel)
    const int N = 10;
    for (int i = 0; i < N; i++) {
        float p = std::fmod((float)i / N + laneOffset, 1.0f);
        float t = p * p;            // quadratic perspective warp
        if (t < 0.006f) continue;   // skip tiny dashes right at horizon

        float sy    = HORIZON + t * (H - HORIZON);
        float roadW = 120.f + 580.f * t;         // road width at this y
        float dw    = roadW * 0.048f;            // dash width = 4.8% of road
        float dh    = std::max(3.f, 18.f * t);  // dash taller near camera

        sf::RectangleShape dash({dw, dh});
        dash.setFillColor(sf::Color(255, 245, 140));
        dash.setOrigin({dw / 2.f, dh / 2.f});
        dash.setPosition({400.f, sy});           // 400 = center of road
        window.draw(dash);
    }
}


// ─────────────────────────────────────────────────────────────────────────────
//  HUD  (text panel + throttle bar + warnings)
// ─────────────────────────────────────────────────────────────────────────────
void drawHUD(sf::RenderWindow& window, sf::Font& font,
             float speed, float rpm, int gear,
             float throttle, float tempF, float fuelPct) {

    bool overheating = (tempF > 240.f);
    bool redline     = (rpm  > 7800.f);

    // Semi-transparent background panel
    sf::RectangleShape panel({215.f, 175.f});
    panel.setPosition({10.f, 10.f});
    panel.setFillColor(sf::Color(0, 0, 0, 150));
    panel.setOutlineThickness(1.f);
    panel.setOutlineColor(sf::Color(0, 180, 160, 100));
    window.draw(panel);

    // Speed
    sf::Text speedTxt(font, "SPD   " + std::to_string((int)speed) + " km/h", 22);
    speedTxt.setFillColor(sf::Color(0, 220, 200));
    speedTxt.setPosition({20.f, 18.f});
    window.draw(speedTxt);

    // RPM — turns red near redline
    sf::Color rpmColor = redline ? sf::Color(255, 55, 55) : sf::Color(0, 220, 200);
    sf::Text rpmTxt(font, "RPM   " + std::to_string((int)rpm), 22);
    rpmTxt.setFillColor(rpmColor);
    rpmTxt.setPosition({20.f, 48.f});
    window.draw(rpmTxt);

    // Gear
    sf::Text gearTxt(font, "GEAR  " + std::to_string(gear), 22);
    gearTxt.setFillColor(sf::Color(255, 210, 50));
    gearTxt.setPosition({20.f, 78.f});
    window.draw(gearTxt);

    // Throttle bar
    sf::RectangleShape barBg({175.f, 13.f});
    barBg.setPosition({20.f, 118.f});
    barBg.setFillColor(sf::Color(35, 35, 35));
    window.draw(barBg);

    sf::RectangleShape bar({throttle * 175.f, 13.f});
    bar.setPosition({20.f, 118.f});
    bar.setFillColor(sf::Color(255, 115, 0));
    window.draw(bar);

    sf::Text throtLbl(font, "THROTTLE", 13);
    throtLbl.setFillColor(sf::Color(170, 170, 170));
    throtLbl.setPosition({20.f, 135.f});
    window.draw(throtLbl);

    // Fuel bar
    sf::RectangleShape fuelBg({175.f, 8.f});
    fuelBg.setPosition({20.f, 158.f});
    fuelBg.setFillColor(sf::Color(35, 35, 35));
    window.draw(fuelBg);

    sf::Color fuelColor = (fuelPct < 0.2f) ? sf::Color(255, 60, 0) : sf::Color(0, 180, 80);
    sf::RectangleShape fuelBar({(fuelPct / 100.f) * 175.f, 8.f});
    fuelBar.setPosition({20.f, 158.f});
    fuelBar.setFillColor(fuelColor);
    window.draw(fuelBar);

    sf::Text fuelLbl(font, "FUEL", 13);
    fuelLbl.setFillColor(sf::Color(170, 170, 170));
    fuelLbl.setPosition({20.f, 170.f});
    window.draw(fuelLbl);

    // ── Warnings ─────────────────────────────────────────────────────────────
    if (overheating) {
        sf::Text warn(font, "!! OVERHEATING !!", 20);
        warn.setFillColor(sf::Color(255, 60, 0));
        warn.setPosition({(float)W / 2.f - 100.f, 14.f});
        window.draw(warn);
    }

    if (redline) {
        sf::Text rl(font, "REDLINE", 18);
        rl.setFillColor(sf::Color(255, 70, 70));
        rl.setPosition({(float)W - 125.f, 16.f});
        window.draw(rl);
    }

    // Controls reminder at bottom
    sf::Text ctrl(font, "W/S = GAS/BRAKE     E/C = SHIFT UP/DOWN     X = QUIT", 13);
    ctrl.setFillColor(sf::Color(110, 110, 110));
    ctrl.setPosition({10.f, (float)H - 24.f});
    window.draw(ctrl);
}

// ─────────────────────────────────────────────────────────────────────────────
//  MAIN
// ─────────────────────────────────────────────────────────────────────────────
int main() {
    SportsCar car;
    sf::Clock clock;
    float laneOffset = 0.f;

    // Load a system font — correct macOS path
    sf::Font font;
    bool hasFont = font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
    if (!hasFont)
        hasFont = font.openFromFile("/System/Library/Fonts/Geneva.ttf");

        sf::Texture carTexture;
        if (!carTexture.loadFromFile("assets/car.png"))
            return -1;
        sf::Sprite carSprite(carTexture);
        carSprite.setOrigin({180.f, 360.f});
        carSprite.setScale({0.95f, 0.95f});
        carSprite.setPosition({400.f, 580.f});

    sf::RenderWindow window(sf::VideoMode({W, H}), "Vehicle Dynamics Simulator");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f;  // cap dt so physics can't explode on lag

        // ── One-shot key events (gear shifts, quit) ───────────────────────────
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::X) window.close();
                if (key->code == sf::Keyboard::Key::E) car.shiftUp();
                if (key->code == sf::Keyboard::Key::C) car.shiftDown();
            }
        }

        // ── Held keys: throttle and brake ────────────────────────────────────
        // accelerate(amount) raises throttle by amount each call
        // liftOff()          gently lowers throttle (engine braking)
        // brake(amount)      lowers throttle AND directly scrubs speed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
            car.accelerate(2.0 * dt);   // full throttle in ~0.5 s
        else
            car.liftOff();              // release gas → engine braking

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
            car.brake(3.0 * dt);        // hard brake

        // ── Physics tick ─────────────────────────────────────────────────────
        car.update(dt);

        // ── Road scroll: faster car = faster lane markings ───────────────────
        laneOffset += (float)(car.getSpeed() * dt * 0.004f);
        if (laneOffset >= 1.f) laneOffset -= 1.f;

        // ── Draw ─────────────────────────────────────────────────────────────
        window.clear(sf::Color(8, 8, 20));
        drawScene(window, laneOffset);
        window.draw(carSprite);
        if (hasFont)
            drawHUD(window, font,
                    (float)car.getSpeed(),
                    (float)car.getRPM(),
                    car.getGear(),
                    (float)car.getThrottle(),
                    (float)car.getTemperature(),
                    car.getFuelPercentage());
        window.display();
    }

    return 0;
}
