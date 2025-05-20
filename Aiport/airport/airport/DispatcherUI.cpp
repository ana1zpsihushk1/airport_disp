#include "Engine.h"
#include "Dispatcher.h"
#include "AirplaneFactory.h"
#include "GameClock.h"

extern GameClock _gameClock;

void Dispatcher::createPlaneWithSchedule() {
    auto role = createRandomRole();

    int now = _gameClock.getTotalSeconds();
    int dep = now - rand() % 300;
    int arr = now + 180 + rand() % 300;

    FlightSchedule sched;
    sched.departureHour = dep / 3600;
    sched.departureMinute = (dep % 3600) / 60;
    sched.arrivalHour = arr / 3600;
    sched.arrivalMinute = (arr % 3600) / 60;

    auto plane = std::make_shared<Airplane>(generatePlaneName(role->getType()),
        std::move(role), sf::seconds(dep));
    plane->setSchedule(sched);
    _airport->acceptAirplane(plane);
    displayPlanes.push_back(plane);

    createPlaneUI(plane);
}

void Dispatcher::createPlaneUI(std::shared_ptr<Airplane> plane) {
    float yOffset = 70.f + displayTexts.size() * 100.f;

    sf::Text text;
    text.setFont(_data->assets.GetFont("plane_Font"));
    text.setCharacterSize(20);
    text.setFillColor(MAIN_WHITE_COLOR);
    text.setPosition(infoPanel.getPosition().x + 20.f, yOffset);

    FlightSchedule sched = plane->getSchedule();
    text.setString(plane->getId() + " | " + sched.getDepartureTimeString() + " - " + sched.getArrivalTimeString());
    displayTexts.push_back(text);

    Button chooseBtn({ 120, 30 }, { infoPanel.getPosition().x + 20.f, yOffset + 30 }, "Choose line", _data->assets.GetFont("plane_Font"));
    chooseBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
    chooseButtons.push_back(chooseBtn);

    Button roundBtn({ 120, 30 }, { infoPanel.getPosition().x + 160.f, yOffset + 30 }, "Next round", _data->assets.GetFont("plane_Font"));
    roundBtn.setColors(BUTTON_MAIN_RED_COLOR, BUTTON_HOVER_RED_COLOR);
    roundButtons.push_back(roundBtn);
}

void Dispatcher::handleChooseLine(std::shared_ptr<Airplane> plane) {
    lineButtons.clear();

    auto& strips = _airport->getStrips();
    float baseY = 70.f + displayTexts.size() * 100.f;
    float x = infoPanel.getPosition().x + 20.f;
    float y = baseY + 70.f;

    for (size_t i = 0; i < strips.size(); ++i) {
        Strip& s = strips[i];
        bool canLand = s.canAccept(*plane->getRole()) && s.isAvailable();

        Button lineBtn({ 30, 30 }, { x + static_cast<float>(i) * 40.f, y }, std::to_string(i + 1), _data->assets.GetFont("plane_Font"));

        if (canLand) {
            lineBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
            s.setHighlightColor(BUTTON_MAIN_COLOR);
        }
        else {
            lineBtn.setColors(BUTTON_MAIN_RED_COLOR, BUTTON_HOVER_RED_COLOR);
            s.setHighlightColor(BUTTON_MAIN_RED_COLOR);
        }

        lineButtons.push_back(lineBtn);
    }
}