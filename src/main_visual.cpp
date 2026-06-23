#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <string>
#include <memory>
#include <deque>
#include "VehicleTypes.h"

const unsigned int W       = 800;
const unsigned int H       = 600;
const float        HORIZON = 280.f;

// ─────────────────────────────────────────────────────────────────────────────
//  SCENE  (sky, grass, road, scrolling lane markings)
// ─────────────────────────────────────────────────────────────────────────────
void drawScene(sf::RenderWindow& window, float laneOffset) {

    // Sky — smooth gradient from deep blue at top to pale sky at horizon
    sf::VertexArray sky(sf::PrimitiveType::TriangleStrip, 4);
    sky[0] = sf::Vertex{{0.f,      0.f},     sf::Color(10,  40, 120)};
    sky[1] = sf::Vertex{{(float)W, 0.f},     sf::Color(10,  40, 120)};
    sky[2] = sf::Vertex{{0.f,      HORIZON}, sf::Color(160, 215, 255)};
    sky[3] = sf::Vertex{{(float)W, HORIZON}, sf::Color(160, 215, 255)};
    window.draw(sky);

    // Sun (drawn before grass so it sits in the sky)
    sf::CircleShape sun(38.f);
    sun.setOrigin({38.f, 38.f});
    sun.setPosition({660.f, 55.f});
    sun.setFillColor(sf::Color(255, 248, 120));
    window.draw(sun);

    // Grass
    sf::RectangleShape grass({(float)W, H - HORIZON});
    grass.setPosition({0.f, HORIZON});
    grass.setFillColor(sf::Color(55, 155, 45));
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
             float throttle, float tempF, float fuelPct, bool wheelspin) {

    bool overheating = (tempF > 240.f);
    bool redline     = (rpm  > 7800.f);

    // Panel background
    sf::RectangleShape panel({240.f, 200.f});
    panel.setPosition({10.f, 10.f});
    panel.setFillColor(sf::Color(5, 5, 10, 175));
    panel.setOutlineThickness(2.f);
    panel.setOutlineColor(sf::Color(0, 200, 180, 160));
    window.draw(panel);

    // Speed
    sf::Text speedTxt(font, "SPD    " + std::to_string((int)speed) + " km/h", 19);
    speedTxt.setFillColor(sf::Color(0, 230, 210));
    speedTxt.setPosition({22.f, 20.f});
    window.draw(speedTxt);

    // RPM
    sf::Color rpmColor = redline ? sf::Color(255, 60, 60) : sf::Color(0, 230, 210);
    sf::Text rpmTxt(font, "RPM    " + std::to_string((int)rpm), 19);
    rpmTxt.setFillColor(rpmColor);
    rpmTxt.setPosition({22.f, 50.f});
    window.draw(rpmTxt);

    // Gear
    sf::Text gearTxt(font, "GEAR   " + std::to_string(gear), 19);
    gearTxt.setFillColor(sf::Color(255, 215, 55));
    gearTxt.setPosition({22.f, 80.f});
    window.draw(gearTxt);

    // Temp
    sf::Color tempColor = (tempF > 240.f) ? sf::Color(255, 60, 0) : sf::Color(0, 230, 210);
    sf::Text tempTxt(font, "TEMP   " + std::to_string((int)tempF) + " F", 19);
    tempTxt.setFillColor(tempColor);
    tempTxt.setPosition({22.f, 110.f});
    window.draw(tempTxt);

    // Throttle bar
    sf::Text throtLbl(font, "THROTTLE", 12);
    throtLbl.setFillColor(sf::Color(140, 140, 140));
    throtLbl.setPosition({22.f, 143.f});
    window.draw(throtLbl);

    sf::RectangleShape barBg({196.f, 10.f});
    barBg.setPosition({22.f, 160.f});
    barBg.setFillColor(sf::Color(40, 40, 40));
    window.draw(barBg);

    sf::RectangleShape bar({throttle * 196.f, 10.f});
    bar.setPosition({22.f, 160.f});
    bar.setFillColor(sf::Color(255, 120, 0));
    window.draw(bar);

    // Fuel bar
    sf::Text fuelLbl(font, "FUEL", 12);
    fuelLbl.setFillColor(sf::Color(140, 140, 140));
    fuelLbl.setPosition({22.f, 176.f});
    window.draw(fuelLbl);

    sf::RectangleShape fuelBg({196.f, 10.f});
    fuelBg.setPosition({22.f, 192.f});
    fuelBg.setFillColor(sf::Color(40, 40, 40));
    window.draw(fuelBg);

    sf::Color fuelColor = (fuelPct < 20.f) ? sf::Color(255, 60, 0) : sf::Color(0, 190, 90);
    sf::RectangleShape fuelBar({(fuelPct / 100.f) * 196.f, 10.f});
    fuelBar.setPosition({22.f, 192.f});
    fuelBar.setFillColor(fuelColor);
    window.draw(fuelBar);

    // ── Warnings ─────────────────────────────────────────────────────────────
    if (overheating) {
        sf::Text warn(font, "!! OVERHEATING !!", 20);
        warn.setFillColor(sf::Color(255, 60, 0));
        warn.setOrigin({warn.getLocalBounds().size.x / 2.f, 0.f});
        warn.setPosition({(float)W / 2.f, 200.f});
        window.draw(warn);
    }

    if (redline) {
        sf::Text rl(font, "REDLINE", 18);
        rl.setFillColor(sf::Color(255, 70, 70));
        rl.setOrigin({rl.getLocalBounds().size.x / 2.f, 0.f});
        rl.setPosition({(float)W / 2.f, 225.f});
        window.draw(rl);
    }

    if (wheelspin) {
        sf::Text ws(font, "WHEELSPIN", 20);
        ws.setFillColor(sf::Color(255, 220, 0));
        ws.setOrigin({ws.getLocalBounds().size.x / 2.f, 0.f});
        ws.setPosition({(float)W / 2.f, 250.f});
        window.draw(ws);
    }

    // Controls reminder at bottom
    sf::Text ctrl(font, "W/S = GAS/BRAKE   E/C = SHIFT   R = CHANGE CAR   X = QUIT", 13);    ctrl.setFillColor(sf::Color(110, 110, 110));
    ctrl.setPosition({10.f, (float)H - 24.f});
    window.draw(ctrl);
}


void drawGauge(sf::RenderWindow& window, sf::Font& font,
               float cx, float cy, float radius,
               float value, float maxValue,
               const std::string& label, sf::Color needleColor) {

    const float START = 135.f;
    const float SWEEP = 240.f;

    // Gauge face
    sf::CircleShape face(radius);
    face.setOrigin({radius, radius});
    face.setPosition({cx, cy});
    face.setFillColor(sf::Color(15, 15, 20, 220));
    face.setOutlineThickness(3.f);
    face.setOutlineColor(needleColor);
    window.draw(face);

    // Tick marks
    const int TICKS = 8;
    for (int i = 0; i <= TICKS; i++) {
        float t     = (float)i / TICKS;
        float angle = (START + t * SWEEP) * 3.14159f / 180.f;
        float outerR = radius * 0.92f;
        float innerR = radius * 0.76f;
        sf::Vertex tick[2] = {
            sf::Vertex{{cx + outerR * std::cos(angle), cy + outerR * std::sin(angle)}, sf::Color(200, 200, 200)},
            sf::Vertex{{cx + innerR * std::cos(angle), cy + innerR * std::sin(angle)}, sf::Color(200, 200, 200)}
        };
        window.draw(tick, 2, sf::PrimitiveType::Lines);
    }

    // Needle
    float ratio      = std::min(value / maxValue, 1.0f);
    float needleAngle = (START + ratio * SWEEP) * 3.14159f / 180.f;
    float needleLen  = radius * 0.70f;
    sf::Vertex needle[2] = {
        sf::Vertex{{cx, cy}, sf::Color::White},
        sf::Vertex{{cx + needleLen * std::cos(needleAngle),
                    cy + needleLen * std::sin(needleAngle)}, needleColor}
    };
    window.draw(needle, 2, sf::PrimitiveType::Lines);

    // Center hub
    float hubR = radius * 0.07f;
    sf::CircleShape hub(hubR);
    hub.setOrigin({hubR, hubR});
    hub.setPosition({cx, cy});
    hub.setFillColor(needleColor);
    window.draw(hub);

    // Label and value
    sf::Text lbl(font, label, 14);
    lbl.setFillColor(sf::Color(180, 180, 180));
    lbl.setOrigin({lbl.getLocalBounds().size.x / 2.f, 0.f});
    lbl.setPosition({cx, cy + radius * 0.40f});
    window.draw(lbl);

    sf::Text val(font, std::to_string((int)value), 18);
    val.setFillColor(needleColor);
    val.setOrigin({val.getLocalBounds().size.x / 2.f, 0.f});
    val.setPosition({cx, cy + radius * 0.58f});
    window.draw(val);
}

void drawTelemetry(sf::RenderWindow& window, sf::Font& font,
                   const std::deque<float>& history) {

    const float PX = 568.f, PY = 10.f;
    const float PW = 220.f, PH = 120.f;
    const float MAX_SPD = 150.f;
    const int   SIZE    = 200;

    sf::RectangleShape bg({PW, PH});
    bg.setPosition({PX, PY});
    bg.setFillColor(sf::Color(0, 0, 0, 150));
    bg.setOutlineThickness(1.f);
    bg.setOutlineColor(sf::Color(0, 180, 160, 100));
    window.draw(bg);

    sf::Text lbl(font, "SPEED TELEMETRY", 12);
    lbl.setFillColor(sf::Color(150, 150, 150));
    lbl.setPosition({PX + 6.f, PY + 4.f});
    window.draw(lbl);

    for (int i = 1; i < (int)history.size(); i++) {
        float x1 = PX + (float)(i - 1) / SIZE * PW;
        float x2 = PX + (float)i       / SIZE * PW;
        float y1 = PY + PH - (history[i - 1] / MAX_SPD) * (PH - 20.f);
        float y2 = PY + PH - (history[i]     / MAX_SPD) * (PH - 20.f);
        sf::Vertex line[2] = {
            sf::Vertex{{x1, y1}, sf::Color(0, 220, 200)},
            sf::Vertex{{x2, y2}, sf::Color(0, 220, 200)}
        };
        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}

int main() {
    std::unique_ptr<Vehicle> car;
    sf::Clock clock;
    float laneOffset = 0.f;
    std::deque<float> speedHistory;
    bool wHeld = false;
    bool sHeld = false;

    // ── Audio ─────────────────────────────────────────────────────────────────
    sf::Music menuMusic;
    sf::Music engineMusic;
    bool hasMenuMusic    = menuMusic.openFromFile("assets/menu.mp3");
    if (hasMenuMusic) {
        menuMusic.setLooping(true);
        menuMusic.setVolume(65.f);
        menuMusic.play();
    }
    
    sf::Font font;
    bool hasFont = font.openFromFile("/System/Library/Fonts/Monaco.ttf");
    if (!hasFont)
        hasFont = font.openFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
    if (!hasFont)
        hasFont = font.openFromFile("/System/Library/Fonts/Geneva.ttf");

        sf::Texture carTexture;
        if (!carTexture.loadFromFile("assets/car.png"))
            return -1;
        sf::Sprite carSprite(carTexture);
        carSprite.setOrigin({180.f, 360.f});
        carSprite.setScale({0.95f, 0.95f});
        carSprite.setPosition({400.f, 580.f});

        sf::Texture truckTexture;
        if (!truckTexture.loadFromFile("assets/truck.png"))
            return -1;
        sf::Sprite truckSprite(truckTexture);
        truckSprite.setOrigin({180.f, 360.f});
        truckSprite.setScale({0.95f, 0.95f});
        truckSprite.setPosition({400.f, 580.f});

        sf::Texture economyTexture;
        if (!economyTexture.loadFromFile("assets/economy.png"))
            return -1;
        sf::Sprite economySprite(economyTexture);
        economySprite.setOrigin({180.f, 360.f});
        economySprite.setScale({0.95f, 0.95f});
        economySprite.setPosition({400.f, 580.f});

    sf::RenderWindow window(sf::VideoMode({W, H}), "Vehicle Dynamics Simulator");
    window.setFramerateLimit(60);

    // ── Vehicle selection screen ──────────────────────────────────────────────
int vehicleType = 1;
car = nullptr;
laneOffset = 0.f;
wHeld = false;
sHeld = false;
while (window.isOpen()) {
bool selected = false;
while (window.isOpen() && !selected) {
    while (const auto event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window.close();
        if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
            if (key->code == sf::Keyboard::Key::Num1) {
                car = std::make_unique<SportsCar>();
                vehicleType = 1;
                selected = true;
            }
            if (key->code == sf::Keyboard::Key::Num2) {
                car = std::make_unique<Truck>();
                vehicleType = 2;
                selected = true;
            }
            if (key->code == sf::Keyboard::Key::Num3) {
                car = std::make_unique<EconomyCar>();
                vehicleType = 3;
                selected = true;
            }
        }
    }
    window.clear(sf::Color(8, 8, 20));
    if (hasFont) {
        sf::Text title(font, "VEHICLE DYNAMICS SIMULATOR", 30);
        title.setFillColor(sf::Color(0, 220, 200));
        title.setOrigin({title.getLocalBounds().size.x / 2.f, 0.f});
        title.setPosition({400.f, 80.f});
        window.draw(title);

        sf::Text opt1(font, "[1]  Sports Car    —  1000 HP  |  9000 RPM", 22);
        opt1.setFillColor(sf::Color(255, 100, 50));
        opt1.setPosition({160.f, 220.f});
        window.draw(opt1);

        sf::Text opt2(font, "[2]  Truck         —   350 HP  |  4500 RPM", 22);
        opt2.setFillColor(sf::Color(200, 200, 200));
        opt2.setPosition({160.f, 270.f});
        window.draw(opt2);

        sf::Text opt3(font, "[3]  Economy Car   —   130 HP  |  6500 RPM", 22);
        opt3.setFillColor(sf::Color(100, 200, 100));
        opt3.setPosition({160.f, 320.f});
        window.draw(opt3);

        sf::Text hint(font, "Press 1, 2, or 3 to select", 16);
        hint.setFillColor(sf::Color(120, 120, 120));
        hint.setOrigin({hint.getLocalBounds().size.x / 2.f, 0.f});
        hint.setPosition({400.f, 420.f});
        window.draw(hint);
    }
    window.display();
}

    // ── Start engine music for selected vehicle ───────────────────────────────
    {
        std::string engineFile = "assets/engine_sports.mp3";
        if (vehicleType == 2)      engineFile = "assets/engine_truck.mp3";
        else if (vehicleType == 3) engineFile = "assets/engine_economy.mp3";
        if (engineMusic.openFromFile(engineFile)) {
            engineMusic.setLooping(true);
            engineMusic.setVolume(70.f);
            engineMusic.play();
        }
        if (hasMenuMusic) menuMusic.setVolume(18.f);
    }

    while (window.isOpen() && selected) {
        float dt = clock.restart().asSeconds();
        if (dt > 0.05f) dt = 0.05f;  // cap dt so physics can't explode on lag

        // ── One-shot key events (gear shifts, quit) ───────────────────────────
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                if (key->code == sf::Keyboard::Key::X) window.close();
                if (key->code == sf::Keyboard::Key::R) selected = false;
                if (key->code == sf::Keyboard::Key::E) car->shiftUp();
                if (key->code == sf::Keyboard::Key::C) car->shiftDown();
                if (key->code == sf::Keyboard::Key::W) wHeld = true;
                if (key->code == sf::Keyboard::Key::S) sHeld = true;
            }

            if (const auto* key = event->getIf<sf::Event::KeyReleased>()) {
               if (key->code == sf::Keyboard::Key::W) wHeld = false;
               if (key->code == sf::Keyboard::Key::S) sHeld = false;
}
        }

        // ── Held keys: throttle and brake ────────────────────────────────────
        // accelerate(amount) raises throttle by amount each call
        // liftOff()          gently lowers throttle (engine braking)
        // brake(amount)      lowers throttle AND directly scrubs speed
        if (wHeld)
            car->accelerate(2.0 * dt);
        else
            car->liftOff();

        if (sHeld)
            car->brake(3.0 * dt);

        // ── Physics tick ─────────────────────────────────────────────────────
        car->update(dt);
        speedHistory.push_back((float)car->getSpeed());
        if ((int)speedHistory.size() > 200) speedHistory.pop_front();

        // ── Road scroll: faster car = faster lane markings ───────────────────
        laneOffset += (float)(car->getSpeed() * dt * 0.032f);
        if (laneOffset >= 1.f) laneOffset -= 1.f;

        // ── Engine sound: pitch and volume follow RPM / throttle ─────────────
        {
            float maxRPM = (vehicleType == 1) ? 9000.f : (vehicleType == 2) ? 4500.f : 6500.f;
            float rpmRatio = (float)car->getRPM() / maxRPM;
            engineMusic.setPitch(0.5f + rpmRatio * 1.5f);
            engineMusic.setVolume(45.f + (float)car->getThrottle() * 35.f);
        }

        // ── Draw ─────────────────────────────────────────────────────────────
        window.clear(sf::Color(8, 8, 20));
        drawScene(window, laneOffset);
        if (vehicleType == 1)      window.draw(carSprite);
        else if (vehicleType == 2) window.draw(truckSprite);
        else                       window.draw(economySprite);

        drawGauge(window, font, 140.f, 490.f, 85.f, (float)car->getRPM(),  9000.f, "RPM",   sf::Color(255, 100,  50));
        drawGauge(window, font, 660.f, 490.f, 85.f, (float)car->getSpeed(), 140.f, "km/h",  sf::Color(  0, 220, 200));
        if (hasFont) drawTelemetry(window, font, speedHistory);


        if (hasFont)
            drawHUD(window, font,
                    (float)car->getSpeed(),
                    (float)car->getRPM(),
                    car->getGear(),
                    (float)car->getThrottle(),
                    (float)car->getTemperature(),
                    car->getFuelPercentage(),
                    car->isWheelspinning());
        window.display();
    }

    // ── Back to selection: stop engine, restore menu music ───────────────────
    engineMusic.stop();
    if (hasMenuMusic) menuMusic.setVolume(65.f);
}
    return 0;
}
