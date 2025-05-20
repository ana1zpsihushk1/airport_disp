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
	}
}

void Dispatcher::update(float dt)
{
	scheduleTexts.clear(); // очищаем перед обновлением

	float yOffset = 70.f; // начальная позиция от заголовка

	if (displayPlanes.size() < 3) // для теста, создать 3 самолета
		createPlaneWithSchedule();

	for (const auto& plane : _airport->getAirplanes())
	{
		const FlightSchedule& sched = plane->getSchedule();
		std::string line = plane->getId() + " | " + sched.getArrivalTimeString() + " - " + sched.getDepartureTimeString();

		sf::Text text;
		text.setFont(*titleText.getFont()); // используем тот же шрифт
		text.setString(line);
		text.setCharacterSize(20); // можно отрегулировать
		text.setFillColor(MAIN_WHITE_COLOR);
		text.setPosition(infoPanel.getPosition().x + 20.f, yOffset);

		yOffset += 30.f; // сдвигаем для следующей строки
		scheduleTexts.push_back(text);
	}
}

void Dispatcher::draw(sf::RenderWindow& window)
{
	window.draw(infoPanel);
	window.draw(titleText);
	for (const auto& text : scheduleTexts)
		window.draw(text);
	if (exitButton) exitButton->draw(window);
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
}

void Dispatcher::issueTakeoff()
{
}

void Dispatcher::issueLanding()
{
}


void Dispatcher::createPlaneWithSchedule() {
	auto role = createRandomRole();

	int now = _gameClock.getTotalSeconds();
	int dep = now - rand() % 300; // from 0 to 5 minutes back
	int arr = now + 180 + rand() % 300; // in 3-8 minutes

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
	text.setFont(_data->assets.GetFont("plane_Font")); // use FONT_FOR_PLANES
	text.setCharacterSize(20);
	text.setFillColor(MAIN_WHITE_COLOR);
	text.setPosition(infoPanel.getPosition().x + 20.f, yOffset);

	const FlightSchedule& sched = plane->getSchedule();
	text.setString(plane->getId() + " | " + sched.getDepartureTimeString() + " - " + sched.getArrivalTimeString());
	displayTexts.push_back(text);

	// Button Choose line
	Button chooseBtn({ 120, 30 }, { infoPanel.getPosition().x + 20.f, yOffset + 30 }, "Choose line", _data->assets.GetFont("plane_Font"));
	chooseBtn.setColors(BUTTON_MAIN_COLOR, BUTTON_HOVER_COLOR);
	chooseButtons.push_back(chooseBtn);

	// Button Next round
	Button roundBtn({ 120, 30 }, { infoPanel.getPosition().x + 160.f, yOffset + 30 }, "Next round", _data->assets.GetFont("plane_Font"));
	roundBtn.setColors(BUTTON_MAIN_RED_COLOR, BUTTON_HOVER_RED_COLOR);
	roundButtons.push_back(roundBtn);
}


void Dispatcher::handleChooseLine(std::shared_ptr<Airplane> plane) {
	// Заглушка — позже тут будет логика подсветки полос
}