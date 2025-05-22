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

	/*
	for (size_t i = 0; i < chooseButtons.size(); ++i)
	{
		chooseButtons[i].update(mousePos);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && chooseButtons[i].isClicked(mousePos))
		{
			float yOffset = chooseLineOffsets[displayPlanes[i]->getId()];
			handleChooseLine(displayPlanes[i], yOffset);
			_selectedPlane = displayPlanes[i];
			return;
		}
	}
	*/

	for (size_t i = 0; i < chooseButtons.size(); ++i)
	{
		chooseButtons[i].update(mousePos);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && chooseButtons[i].isClicked(mousePos))
		{
			auto plane = displayPlanes[i];
			auto parkingRoute = plane->getParkingRoute();
			std::reverse(parkingRoute.begin(), parkingRoute.end());

			std::vector<sf::Vector2f> path = parkingRoute;

			// Выбираем случайный путь взлёта
			std::string type = plane->getRole()->getType();
			std::vector<sf::Vector2f> takeoffPath;

			if (type == "Cargo" || type == "WideBody")
			{
				static std::vector<std::vector<sf::Vector2f>> bigRoutes = { TAKEOFF_BIG_1, TAKEOFF_BIG_2 };
				takeoffPath = bigRoutes[rand() % bigRoutes.size()];
			}
			else
			{
				static std::vector<std::vector<sf::Vector2f>> smallRoutes = {
					TAKEOFF_SMALL_1, TAKEOFF_SMALL_2, TAKEOFF_SMALL_3,
					TAKEOFF_SMALL_4, TAKEOFF_SMALL_5
				};
				takeoffPath = smallRoutes[rand() % smallRoutes.size()];
			}

			path.insert(path.end(), takeoffPath.begin(), takeoffPath.end());

			if (takeoffPath.size() >= 2) {
				sf::Vector2f dir = takeoffPath.back() - takeoffPath[takeoffPath.size() - 2];
				float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (len > 0) {
					dir /= len;
					plane->setLastDirection(dir);
					sf::Vector2f offscreenTarget = takeoffPath.back() + dir * 1000.f;
					path.push_back(offscreenTarget);
				}
			}

			plane->setPath(path);
			plane->setStatus(Status::takingOff);
			plane->setVisible(true);
			plane->setMoving(true);
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

	/*for (auto& [button, strip] : lineButtons) {
		button.update(mousePos);
		if (_selectedPlane && strip->canAccept(*_selectedPlane->getRole())) {
			_selectedPlane->assignStrip(strip);
			sf::Time now = sf::seconds(_gameClock.getTotalSeconds());
			strip->reserveUntil(now + sf::seconds(10));

			std::vector<sf::Vector2f> path;

			// Получаем маршрут от парковки (развёрнутый)
			auto unparkPath = _selectedPlane->getParkingRoute();
			std::reverse(unparkPath.begin(), unparkPath.end());
			path.insert(path.end(), unparkPath.begin(), unparkPath.end());

			// Добавляем путь взлёта
			auto takeoffPath = strip->getTakeoffPath();
			path.insert(path.end(), takeoffPath.begin(), takeoffPath.end());

			if (takeoffPath.size() >= 2) {
				sf::Vector2f dir = takeoffPath.back() - takeoffPath[takeoffPath.size() - 2];
				float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
				if (len > 0) {
					dir /= len;
					_selectedPlane->setLastDirection(dir);
					sf::Vector2f offscreenTarget = takeoffPath.back() + dir * 1000.f;
					path.push_back(offscreenTarget);
				}
			}

			_selectedPlane->setPath(path);
			_selectedPlane->setStatus(Status::takingOff);
			_selectedPlane->setVisible(true);
			_selectedPlane->setMoving(true);

			lineButtons.clear();
		}
	}*/
}

void Dispatcher::update(float dt)
{
	scheduleTexts.clear();

	float yOffset = 70.f;

	if (displayPlanes.size() < 5)
	{
		//createdTypes.clear();
		createPlaneWithSchedule();
	}

	sf::Time currentTime = sf::seconds(_gameClock.getTotalSeconds());

	for (auto& plane : _airport->getAirplanes())
		plane->update(sf::seconds(dt), currentTime);

	for (auto it = displayPlanes.begin(); it != displayPlanes.end(); )
	{
		auto& plane = *it;

		if (plane->getStatus() == Status::crashed) {
			_airport->deleteAirplane(plane->getId());
			it = displayPlanes.erase(it);
			continue;
		}

		if (plane->getStatus() == Status::inAir && !plane->isVisible()) {
			_airport->deleteAirplane(plane->getId());
			it = displayPlanes.erase(it);
			continue;
		}

		if (plane->getStatus() == Status::inAir && plane->getShape().getPosition().y < 0) {
			_airport->deleteAirplane(plane->getId());
			it = displayPlanes.erase(it);
			continue;
		}

		if (plane->getStatus() == Status::landed && !plane->isMoving()) {
			it = displayPlanes.erase(it);
			continue;
		}

		++it;
	}

	for (const auto& plane : _airport->getAirplanes())
	{
		const FlightSchedule& sched = plane->getSchedule();

		std::string mainLine;
		if (plane->getStatus() == Status::awaitingTakeoff && !plane->getArrival())
			mainLine = plane->getId();
		else
			mainLine = plane->getId() + " | " + sched.getDepartureTimeString() + " - " + sched.getArrivalTimeString();

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

	// for (auto& button : lineButtons)
	//	button.draw(window);

	for (const auto& text : scheduleTexts)
		window.draw(text);

	if (exitButton) 
		exitButton->draw(window);

	sf::Font& font = _data->assets.GetFont("plane_Font");

	/*for (const auto& strip : _airport->getStrips())
	{
		const auto& landingPath = strip->getLandingPath();
		if (landingPath.size() >= 2)
		{
			sf::VertexArray lines(sf::TriangleStrip);
			sf::Color color = strip->isAvailable() ? BUTTON_MAIN_COLOR : BUTTON_MAIN_RED_COLOR;
			color.a = 120;

			float thickness = 10.f;
			for (size_t i = 0; i < landingPath.size() - 1; ++i)
			{
				sf::Vector2f p1 = landingPath[i];
				sf::Vector2f p2 = landingPath[i + 1];
				sf::Vector2f direction = p2 - p1;
				float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
				if (length == 0) continue;
				sf::Vector2f normal = { -direction.y / length, direction.x / length };
				sf::Vector2f offset = normal * thickness / 2.f;

				lines.append(sf::Vertex(p1 + offset, color));
				lines.append(sf::Vertex(p1 - offset, color));
			}
			sf::Vector2f lastOffset = (landingPath.back() - landingPath[landingPath.size() - 2]);
			float len = std::hypot(lastOffset.x, lastOffset.y);
			if (len != 0) lastOffset = { -lastOffset.y / len, lastOffset.x / len };
			lastOffset *= thickness / 2.f;

			lines.append(sf::Vertex(landingPath.back() + lastOffset, color));
			lines.append(sf::Vertex(landingPath.back() - lastOffset, color));

			window.draw(lines);
		}
	}

	//sf::Font& font = _data->assets.GetFont("plane_Font");

	for (auto& [button, strip] : lineButtons)
	{
		if (button.isHovered(sf::Mouse::getPosition()))
		{
			const auto& path = strip->getLandingPath();
			if (path.size() >= 2)
			{
				sf::VertexArray lines(sf::LineStrip, path.size());
				sf::Color color = strip->isAvailable() ? BUTTON_MAIN_COLOR : BUTTON_MAIN_RED_COLOR;
				color.a = 140;

				for (size_t i = 0; i < path.size(); ++i)
				{
					lines[i].position = path[i];
					lines[i].color = color;
				}
				window.draw(lines);

				// Номер полосы
				sf::Text label;
				label.setFont(font);
				label.setCharacterSize(18);
				label.setString("Strip " + std::to_string(stripIndex(strip)));
				label.setFillColor(color);
				label.setPosition(path.back().x + 10.f, path.back().y - 10.f);
				window.draw(label);
			}
		}

		button.draw(window);
	}*/

	/*for (auto& [button, strip] : lineButtons)
	{
		if (button.isHovered(sf::Mouse::getPosition()))
		{
			const auto& path = strip->getLandingPath(); // Используем как универсальный путь для отрисовки
			if (path.size() >= 2)
			{
				sf::VertexArray lines(sf::LineStrip, path.size());
				sf::Color color = strip->isAvailable() ? BUTTON_MAIN_COLOR : BUTTON_MAIN_RED_COLOR;
				color.a = 140;

				for (size_t i = 0; i < path.size(); ++i)
				{
					lines[i].position = path[i];
					lines[i].color = color;
				}
				window.draw(lines);

				sf::RectangleShape box;
				box.setSize({ 40.f, 25.f });
				box.setFillColor(MAIN_WHITE_COLOR);
				box.setOutlineColor(BUTTON_MAIN_COLOR);
				box.setOutlineThickness(2.f);
				box.setPosition(path.back().x + 10.f, path.back().y - 10.f);

				sf::Text label;
				label.setFont(font);
				label.setCharacterSize(16);
				label.setStyle(sf::Text::Bold);
				label.setString(std::to_string(stripIndex(strip)));
				label.setFillColor(MAIN_BLACK_COLOR);
				label.setPosition(box.getPosition().x + 10.f, box.getPosition().y + 2.f);

				window.draw(box);
				window.draw(label);
			}
		}

		button.draw(window);
	}*/
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

	// Кнопка Exit
	sf::Vector2f exitSize(100, 40);
	sf::Vector2f exitPos(infoPanel.getPosition().x + 20.f, SCREEN_HEIGHT - 60.f);
	exitButton = new Button(exitSize, exitPos, "Exit", font);
}

void Dispatcher::selectPlane(const sf::Vector2i& mousePos)
{
	for (const auto& plane : displayPlanes)
	{
		sf::FloatRect bounds = plane->getShape().getGlobalBounds();
		if (bounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
		{
			_selectedPlane = plane;
			handleChooseLine(plane, chooseLineOffsets[plane->getId()]);
			break;
		}
	}
}

void Dispatcher::issueTakeoff()
{
}

void Dispatcher::issueLanding()
{
}

/*
void Dispatcher::createPlaneWithSchedule() {
	//static std::set<std::string> createdTypes; // чтобы избежать дубликатов

	std::vector<std::string> types = { "Local", "Regional", "NarrowBody", "Cargo", "WideBody" };

	/*for (const std::string& type : types)
	{
		if (createdTypes.find(type) != createdTypes.end()) continue;

		auto role = createRoleByType(type);
		std::string planeId = generatePlaneName(role->getType());
		int now = _gameClock.getTotalSeconds();

		// Определим сценарий — взлёт или посадка
		bool isDeparture = rand() % 2 == 0;

		int spacing = FLIGHT_DAY_DURATION / MAX_FLIGHTS_PER_DAY;
		int baseTime = spacing * flightCounter + 300;
		flightCounter++;

		int dep = baseTime;
		int arr = dep + 180;

		if (!isDeparture) std::swap(dep, arr);

		FlightSchedule sched;
		sched.departureHour = dep / 3600;
		sched.departureMinute = (dep % 3600) / 60;
		sched.arrivalHour = arr / 3600;
		sched.arrivalMinute = (arr % 3600) / 60;

		auto plane = std::make_shared<Airplane>(planeId, std::move(role), sf::seconds(dep));
		plane->setSchedule(sched);
		plane->setDisplayName(planeId);

		sf::Texture& tex = _data->assets.GetTexture("AIRPLANE_PNG");
		sf::Vector2f startPos;
		std::vector<sf::Vector2f> path;

		if (isDeparture)
		{
			plane->setStatus(Status::awaitingTakeoff);
			plane->setArrival(false);
			path = chooseTakeoffPathByType(type); 
			startPos = path.front();

			plane->setVisible(true); 
			plane->setMoving(false);
		}
		else
		{
			plane->setStatus(Status::inAir);
			plane->setArrival(true);
			path = chooseLandingPathByType(type); 
			startPos = path.front();

			auto parkingRoute = assignParking(plane);
			path.insert(path.end(), parkingRoute.begin(), parkingRoute.end());
		}

		plane->setPath(path);
		plane->getShape().setTexture(&tex);
		plane->getShape().setRadius(20.f); 
		plane->getShape().setOrigin(20.f, 20.f);
		plane->getShape().setPosition(startPos);

		_airport->acceptAirplane(plane);
		displayPlanes.push_back(plane);

		createPlaneUI(plane, nextPlaneUI_YOffset);

		createdTypes.insert(type);
	}//

	int planesToGenerate = 10;
	int spacing = FLIGHT_DAY_DURATION / planesToGenerate;

	for (int i = 0; i < planesToGenerate; ++i)
	{
		std::string type = types[rand() % types.size()];
		auto role = createRoleByType(type);
		std::string planeId = generatePlaneName(role->getType());

		int now = _gameClock.getTotalSeconds();

		// Время вылета/прилёта
		int baseTime = spacing * i + 300; // немного отступим от нуля
		int dep = baseTime;
		int arr = dep + 180;

		bool isDeparture = rand() % 2 == 0;
		if (!isDeparture) std::swap(dep, arr);

		FlightSchedule sched;
		sched.departureHour = dep / 3600;
		sched.departureMinute = (dep % 3600) / 60;
		sched.arrivalHour = arr / 3600;
		sched.arrivalMinute = (arr % 3600) / 60;

		auto plane = std::make_shared<Airplane>(planeId, std::move(role), sf::seconds(dep));
		plane->setSchedule(sched);
		plane->setDisplayName(planeId);

		sf::Texture& tex = _data->assets.GetTexture(AIRPLANE_PNG);
		plane->getShape().setTexture(&tex);
		plane->getShape().setRadius(20.f);
		plane->getShape().setOrigin(20.f, 20.f);

		std::vector<sf::Vector2f> path;
		sf::Vector2f startPos;

		if (isDeparture)
		{
			plane->setStatus(Status::awaitingTakeoff);
			plane->setArrival(false);

			auto parkingRoute = assignParking(plane);
			plane->setParkingRoute(parkingRoute);

			auto takeoffRoute = chooseTakeoffPathByType(type);

			std::vector<sf::Vector2f> reverseParking = parkingRoute;
			std::reverse(reverseParking.begin(), reverseParking.end());

			path = reverseParking;
			path.insert(path.end(), takeoffRoute.begin(), takeoffRoute.end());

			startPos = path.front();

			plane->setVisible(true);
			plane->setMoving(false);
		}
		else
		{
			plane->setStatus(Status::inAir);
			plane->setArrival(true);
			path = chooseLandingPathByType(type);
			startPos = path.front();

			auto parkingRoute = assignParking(plane);
			plane->setParkingRoute(parkingRoute);
			path.insert(path.end(), parkingRoute.begin(), parkingRoute.end());
		}

		plane->setPath(path);
		plane->getShape().setPosition(startPos);

		_airport->acceptAirplane(plane);
		displayPlanes.push_back(plane);
		createPlaneUI(plane, nextPlaneUI_YOffset);
	}
}
*/

void Dispatcher::createPlaneWithSchedule() {
	std::vector<std::string> types = { "Local", "Regional", "NarrowBody", "Cargo", "WideBody" };

	int count = rand() % 4 + 3; // от 3 до 6 самолётов
	for (int i = 0; i < count; ++i) {
		std::string type = types[rand() % types.size()];
		auto role = createRoleByType(type);
		std::string planeId = generatePlaneName(role->getType());

		auto plane = std::make_shared<Airplane>(planeId, std::move(role), sf::seconds(0));
		plane->setDisplayName(planeId);
		plane->setStatus(Status::awaitingTakeoff);
		plane->setArrival(false);

		sf::Texture& tex = _data->assets.GetTexture(AIRPLANE_PNG);
		plane->getShape().setTexture(&tex);
		plane->getShape().setRadius(20.f);
		plane->getShape().setOrigin(20.f, 20.f);

		auto parkingRoute = assignParking(plane);
		plane->setParkingRoute(parkingRoute);

		if (!parkingRoute.empty())
			plane->getShape().setPosition(parkingRoute.back());

		plane->setVisible(true);
		plane->setMoving(false);

		_airport->acceptAirplane(plane);
		displayPlanes.push_back(plane);

		createPlaneUI(plane, nextPlaneUI_YOffset);
	}
}

std::vector<sf::Vector2f> Dispatcher::assignParking(std::shared_ptr<Airplane> plane)
{
	if (plane->getRole()->getType() == "Cargo" || plane->getRole()->getType() == "WideBody")
	{
		for (int i = 0; i < PARKING_BIG_ROUTES.size(); ++i) {
			int parkingId = 56 + i;
			if (!bigParkingOccupied[parkingId]) {
				bigParkingOccupied[parkingId] = true;
				plane->setParkingId(parkingId);
				return PARKING_BIG_ROUTES[i];
			}
		}
	}
	else
	{
		for (int i = 0; i < PARKING_SMALL_ROUTES.size(); ++i) {
			int parkingId = 45 + i;
			if (!smallParkingOccupied[parkingId]) {
				smallParkingOccupied[parkingId] = true;
				plane->setParkingId(parkingId);
				return PARKING_SMALL_ROUTES[i];
			}
		}
	}
	return {};
}

void Dispatcher::resetGame()
{
	_airport->reset();
	displayPlanes.clear();
	chooseButtons.clear();
	roundButtons.clear();
	lineButtons.clear();
	scheduleTexts.clear();

	//createdTypes.clear();
}

int Dispatcher::stripIndex(const std::shared_ptr<Strip>& target)
{
	auto& strips = _airport->getStrips();
	for (size_t i = 0; i < strips.size(); ++i)
	{
		if (strips[i] == target)
			return static_cast<int>(i + 1);
	}
	return -1;
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

	/*Button chooseBtn({155, 40}, {infoPanel.getPosition().x + 20.f, buttonY}, "Choose line", _data->assets.GetFont("plane_Font"));
	chooseBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
	chooseButtons.push_back(chooseBtn);

	Button roundBtn({ 155, 40 }, { infoPanel.getPosition().x + 210.f, buttonY }, "Next round", _data->assets.GetFont("plane_Font"));
	roundBtn.setColors(BUTTON_MAIN_RED_COLOR, BUTTON_HOVER_RED_COLOR);
	roundButtons.push_back(roundBtn);

	chooseButtons.push_back(chooseBtn);
	roundButtons.push_back(roundBtn);
	chooseLineOffsets[plane->getId()] = yOffset;*/

	Button takeoffBtn({ 155, 40 }, { infoPanel.getPosition().x + 20.f, buttonY }, "Take off", _data->assets.GetFont("plane_Font"));
	takeoffBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
	chooseButtons.push_back(takeoffBtn);
}

/*
void Dispatcher::handleChooseLine(std::shared_ptr<Airplane> plane, float yOffset) {
	lineButtons.clear();
	auto& strips = _airport->getStrips();
	float baseY = yOffset;

	float x = infoPanel.getPosition().x + 20.f;
	float y = baseY + 570.f;

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
		lineButtons.emplace_back(lineBtn, s);
	}
}
*/

void Dispatcher::handleChooseLine(std::shared_ptr<Airplane> plane, float yOffset) {
	lineButtons.clear();
	auto& strips = _airport->getStrips();

	float x = infoPanel.getPosition().x + 20.f;
	float y = yOffset + 570.f;

	for (size_t i = 0; i < strips.size(); ++i) {
		auto& s = strips[i];
		if (s->canAccept(*plane->getRole()) && s->isAvailable()) {
			Button lineBtn({ 30, 30 }, { x + static_cast<float>(i) * 40.f, y }, std::to_string(i + 1), _data->assets.GetFont("plane_Font"));
			lineBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
			s->setHighlightColor(BUTTON_MAIN_COLOR);

			lineButtons.emplace_back(lineBtn, s);
		}
	}
}
