#include <algorithm>
#include <set>

#include "Dispatcher.h"
#include "menuState.h"
#include "AirplaneUtils.h"
#include "GameClock.h"
#include "AirplaneFactory.h"

extern GameClock _gameClock;

Dispatcher::Dispatcher(std::shared_ptr<AirportPlayer> airport, GameDataRef data,
	sf::Font& font): _airport(airport), _data(data)
{
	initUI(font);
}

void Dispatcher::handleInput(const sf::Vector2i& mousePos)
{
	selectPlane(mousePos);

	exitButton->update(mousePos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && exitButton->isClicked(mousePos))
	{
		_data->engine->PlayMainTheme();
		_data->machine.AddState(StateRef(new menuState(_data)), true);
		return;
	}

	for (size_t i = 0; i < chooseButtons.size(); ++i)
	{
		chooseButtons[i].update(mousePos);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && chooseButtons[i].isClicked(mousePos))
		{
			handleChooseLine(displayPlanes[i]);
			_selectedPlane = displayPlanes[i];
			return;
		}
	}

	for (size_t i = 0; i < roundButtons.size(); ++i)
	{
		roundButtons[i].update(mousePos);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && roundButtons[i].isClicked(mousePos))
		{
			auto plane = displayPlanes[i];
			auto now = sf::seconds(_gameClock.getTotalSeconds());

			if (plane->getStatus() == Status::awaitingTakeoff)
				plane->requestTakeoff(_airport->getStrips(), now);

			else if (plane->getStatus() == Status::inAir || plane->getStatus() == Status::getCircle)
				plane->requestLanding(_airport->getStrips(), now);
		}
	}

	for (size_t i = 0; i < lineButtons.size(); ++i)
	{
		lineButtons[i].update(mousePos);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && lineButtons[i].isClicked(mousePos))
		{
			auto& strip = _airport->getStrips()[i];
			if (_selectedPlane && strip->canAccept(*_selectedPlane->getRole()))
			{
				_selectedPlane->assignStrip(strip);
				lineButtons.clear();
			}
		}
	}
}

void Dispatcher::update(float dt)
{
	scheduleTexts.clear();

	float yOffset = 70.f;

	if (displayPlanes.size() < 5)
	{
		createdTypes.clear();
		createPlaneWithSchedule();
	}

	sf::Time currentTime = sf::seconds(_gameClock.getTotalSeconds());

	for (auto& plane : _airport->getAirplanes())
		plane->update(sf::seconds(dt), currentTime);

	for (auto it = displayPlanes.begin(); it != displayPlanes.end(); )
	{
		auto& plane = *it;
		if (plane->getStatus() == Status::landed || plane->getStatus() == Status::crashed ||
			(plane->getStatus() == Status::inAir && plane->getShape().getPosition().y < 0))
		{
			_airport->deleteAirplane(plane->getId());
			it = displayPlanes.erase(it);
		}
		else
			++it;
	}

	for (const auto& plane : _airport->getAirplanes())
	{
		const FlightSchedule& sched = plane->getSchedule();

		std::string mainLine = plane->getId() + " | " + sched.getDepartureTimeString() + " - " + sched.getArrivalTimeString();
		std::string planeStatus;
		sf::Color statusColor = MAIN_WHITE_COLOR;

		switch (plane->getStatus()) {
		case Status::awaitingTakeoff:
		case Status::takingOff:
			planeStatus = "   -> Takeoff";
			break;
		case Status::inAir:
		case Status::awaitingLanding:
		case Status::landing:
			planeStatus = "   <- Landing";
			break;
		case Status::getCircle:
			planeStatus = "   # Circle (" + std::to_string(plane->getRemainingCircles()) + " left)";
			statusColor = ATTINTION_COLOR;
			break;
		case Status::landed:
			planeStatus = "     + Landed";
			break;
		case Status::crashed:
			planeStatus = "     * Crashed";
			statusColor = ATTINTION_COLOR;
			break;
		default:
			planeStatus = "";
			break;
		}

		sf::Text text1;
		text1.setFont(*titleText.getFont());
		text1.setString(mainLine);
		text1.setCharacterSize(20);
		text1.setFillColor(MAIN_WHITE_COLOR);
		text1.setPosition(infoPanel.getPosition().x + 20.f, yOffset);
		yOffset += 25.f;

		sf::Text text2;
		text2.setFont(*titleText.getFont());
		text2.setString(planeStatus);
		text2.setCharacterSize(18);
		text2.setFillColor(statusColor);
		text2.setPosition(infoPanel.getPosition().x + 40.f, yOffset);
		nextPlaneUI_YOffset = yOffset;
		yOffset += 90.f;

		scheduleTexts.push_back(text1);
		scheduleTexts.push_back(text2);
	}
}

void Dispatcher::draw(sf::RenderWindow& window)
{
	window.draw(infoPanel);
	window.draw(titleText);

	sf::Font& planeFont = _data->assets.GetFont(FONT_FOR_PLANES);

	for (const auto& plane : _airport->getAirplanes())
	{
		if (plane->isVisible())
			plane->draw(window, planeFont);
	}

	for (auto& button : chooseButtons)
		button.draw(window);

	for (auto& button : roundButtons)
		button.draw(window);

	for (auto& button : lineButtons)
		button.draw(window);

	for (const auto& text : scheduleTexts)
		window.draw(text);
	if (exitButton) 
		exitButton->draw(window);
}

void Dispatcher::initUI(sf::Font& font)
{
	infoPanel.setSize(sf::Vector2f(450.f, static_cast<float>(SCREEN_HEIGHT)));
	infoPanel.setFillColor(INFO_PANEL_COLOR);
	infoPanel.setPosition(SCREEN_WIDTH - 450.f, 0.f);

	titleText.setFont(font);
	titleText.setString("Timetable");
	titleText.setCharacterSize(28); // size of font
	titleText.setFillColor(MAIN_WHITE_COLOR);

	sf::FloatRect bounds = titleText.getLocalBounds();
	titleText.setOrigin(bounds.width / 2.f, 0.f);
	titleText.setPosition(infoPanel.getPosition().x + infoPanel.getSize().x / 2.f, 20.f);

	//  нопка Exit
	sf::Vector2f exitSize(100, 40);
	sf::Vector2f exitPos(infoPanel.getPosition().x + 20.f, SCREEN_HEIGHT - 60.f);
	exitButton = new Button(exitSize, exitPos, "Exit", font);
}

void Dispatcher::selectPlane(const sf::Vector2i& mousePos)
{
}

void Dispatcher::issueTakeoff()
{
}

void Dispatcher::issueLanding()
{
}

void Dispatcher::createPlaneWithSchedule() {
	//static std::set<std::string> createdTypes; // чтобы избежать дубликатов

	std::vector<std::string> types = { "Local", "Regional", "NarrowBody", "Cargo", "WideBody" };

	for (const std::string& type : types)
	{
		if (createdTypes.find(type) != createdTypes.end()) continue;

		auto role = createRoleByType(type);
		std::string planeId = generatePlaneName(role->getType());
		int now = _gameClock.getTotalSeconds();

		// ќпределим сценарий Ч взлЄт или посадка
		bool isDeparture = rand() % 2 == 0;

		int dep = now + 30 + rand() % 120; // от 30 до 2.5 мин в будущем
		int arr = now + 60 + rand() % 180; // прилЄт чуть позже

		if (!isDeparture) std::swap(dep, arr); // если это посадка Ч прилет раньше

		FlightSchedule sched;
		sched.departureHour = dep / 3600;
		sched.departureMinute = (dep % 3600) / 60;
		sched.arrivalHour = arr / 3600;
		sched.arrivalMinute = (arr % 3600) / 60;

		auto plane = std::make_shared<Airplane>(planeId, std::move(role), sf::seconds(dep));
		plane->setSchedule(sched);
		plane->setDisplayName(planeId); // дл€ UI

		sf::Texture& tex = _data->assets.GetTexture("AIRPLANE_PNG");
		sf::Vector2f startPos;
		std::vector<sf::Vector2f> path;

		if (isDeparture)
		{
			plane->setStatus(Status::awaitingTakeoff);
			path = chooseTakeoffPathByType(type); // random из возможных
			startPos = path.front();
		}
		else
		{
			plane->setStatus(Status::inAir);
			path = chooseLandingPathByType(type); // random из возможных
			startPos = path.front();
		}

		plane->setPath(path);
		plane->getShape().setTexture(&tex);
		plane->getShape().setRadius(20.f); // или что подходит
		plane->getShape().setOrigin(20.f, 20.f); // центр
		plane->getShape().setPosition(startPos);

		_airport->acceptAirplane(plane);
		displayPlanes.push_back(plane);

		createPlaneUI(plane, nextPlaneUI_YOffset);

		createdTypes.insert(type);
	}
}

void Dispatcher::resetGame()
{
	_airport->reset();
	displayPlanes.clear();
	chooseButtons.clear();
	roundButtons.clear();
	lineButtons.clear();
	scheduleTexts.clear();
	createdTypes.clear();
}

std::vector<sf::Vector2f> Dispatcher::chooseTakeoffPathByType(const std::string& type)
{
	static std::vector<std::vector<sf::Vector2f>> big = { TAKEOFF_BIG_1, TAKEOFF_BIG_2 };
	static std::vector<std::vector<sf::Vector2f>> small = { TAKEOFF_SMALL_1, TAKEOFF_SMALL_2, TAKEOFF_SMALL_3, TAKEOFF_SMALL_4, TAKEOFF_SMALL_5 };

	if (type == "Cargo" || type == "WideBody")
		return big[rand() % big.size()];
	else
		return small[rand() % small.size()];
}

std::vector<sf::Vector2f> Dispatcher::chooseLandingPathByType(const std::string& type)
{
	static std::vector<std::vector<sf::Vector2f>> big = { LANDING_BIG_1, LANDING_BIG_2 };
	static std::vector<std::vector<sf::Vector2f>> small = { LANDING_SMALL_1, LANDING_SMALL_2, LANDING_SMALL_3, LANDING_SMALL_4, LANDING_SMALL_5 };

	if (type == "Cargo" || type == "WideBody")
		return big[rand() % big.size()];
	else
		return small[rand() % small.size()];
}

void Dispatcher::createPlaneUI(std::shared_ptr<Airplane> plane, float yOffset) {
	sf::Text text;
	text.setFont(_data->assets.GetFont("plane_Font"));
	text.setCharacterSize(20);
	text.setFillColor(MAIN_WHITE_COLOR);
	text.setPosition(infoPanel.getPosition().x + 20.f, yOffset);

	FlightSchedule sched = plane->getSchedule();
	text.setString(plane->getId() + " | " + sched.getDepartureTimeString() + " - " + sched.getArrivalTimeString());
	displayTexts.push_back(text);

	float buttonY = yOffset + 50.f;

	Button chooseBtn({ 155, 40 }, { infoPanel.getPosition().x + 20.f, buttonY }, "Choose line", _data->assets.GetFont("plane_Font"));
	chooseBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
	chooseButtons.push_back(chooseBtn);

	Button roundBtn({ 155, 40 }, { infoPanel.getPosition().x + 210.f, buttonY }, "Next round", _data->assets.GetFont("plane_Font"));
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
		auto& s = strips[i];
		bool canLand = s->canAccept(*plane->getRole()) && s->isAvailable();
		Button lineBtn({ 30, 30 }, { x + static_cast<float>(i) * 40.f, y }, std::to_string(i + 1), _data->assets.GetFont("plane_Font"));
		if (canLand) {
			lineBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
			s->setHighlightColor(BUTTON_MAIN_COLOR);
		}
		else {
			lineBtn.setColors(BUTTON_MAIN_RED_COLOR, BUTTON_HOVER_RED_COLOR);
			s->setHighlightColor(BUTTON_MAIN_RED_COLOR);
		}
		lineButtons.push_back(lineBtn);
	}
}