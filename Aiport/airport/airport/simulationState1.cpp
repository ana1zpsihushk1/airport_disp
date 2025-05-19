#include "simulationState1.h"
#include "definitions.h"
#include "menuState.h"
#include "GameClock.h"

GameClock _gameClock;

simulationState1::simulationState1(GameDataRef data) : _data(data) {}

/*void simulationState1::Init()
{
	const int windowWidth = SCREEN_WIDTH;
	const int windowHeight = SCREEN_HEIGHT;

	_data->engine->PlayGameTheme();

	_data->assets.LoadFont("plane_Font", FONT_FOR_PLANES);
	const sf::Font& planeFont = _data->assets.GetFont("plane_Font");

	sf::Vector2f airportSize(300, 200);
	sf::Vector2f playerPos(windowWidth - airportSize.x - 20, 20);
	sf::Vector2f npcPos(20, windowHeight - airportSize.y - 20);

	AirPlayer = std::make_shared<AirportPlayer>(playerPos, airportSize);
	AirNpc = std::make_shared<AirportNpc>(npcPos, airportSize);
	AirPlayer->initStrip();
	AirNpc->initStrip();

	auto plane = std::make_shared<Airplane>(
		"Plane_" + std::to_string(planeId++),
		createRandomRole(),
		planeFont
	);
	plane->setPosition({ npcPos.x + 100, npcPos.y + 50 });
	activePlanes.push_back(plane);
	AirNpc->acceptAirplane(plane);
}

void simulationState1::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_data->window.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			_data->machine.AddState(StateRef(new menuState(_data)), true); // Вернуться в меню
	}
}

void simulationState1::Update(float dt)
{
	_gameClock.update(dt);
	AirPlayer->tick();
	AirNpc->tick();
	AirNpc->processTakeoff();

	for (auto& plane : activePlanes)
	{
		plane->tick();
	}
}

void simulationState1::Draw(float dt)
{
	_data->window.clear(sf::Color(MAIN_SCREEN_COLOR));

	AirPlayer->draw(_data->window);
	AirNpc->draw(_data->window);

	for (auto& p : activePlanes)
	{
		p->draw(_data->window);
	}

	sf::Text clockText;
	clockText.setFont(_data->assets.GetFont("menu_Font"));
	clockText.setCharacterSize(32);
	clockText.setFillColor(MAIN_BLACK_COLOR);
	clockText.setString("Time: " + _gameClock.getTimeString());
	clockText.setPosition(20, 20);

	_data->window.draw(clockText);

	_data->window.display();
}*/


void simulationState1::Init()
{
	const int windowWidth = SCREEN_WIDTH;
	const int windowHeight = SCREEN_HEIGHT;

	_data->engine->PlayGameTheme();

	_data->assets.LoadFont("plane_Font", FONT_FOR_PLANES);
	_data->assets.LoadTexture("game_background", MAIN_GAME_PNG);

	backgroundSprite.setTexture(_data->assets.GetTexture("game_background"));

	sf::Vector2f airportSize(300, 200);
	sf::Vector2f playerPos(windowWidth - airportSize.x - 20, 20);

	AirPlayer = std::make_shared<AirportPlayer>(playerPos, airportSize);
	AirPlayer->initStrip();
}

void simulationState1::HandleInput()
{
	sf::Event event;
	while (_data->window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			_data->window.close();

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
			_data->machine.AddState(StateRef(new menuState(_data)), true);
	}
}

void simulationState1::Update(float dt)
{
	_gameClock.update(dt);
	AirPlayer->tick();
}

void simulationState1::Draw(float dt)
{
	_data->window.clear(sf::Color(185, 210, 156));

	_data->window.draw(backgroundSprite);
	AirPlayer->draw(_data->window);

	sf::Text clockText;
	clockText.setFont(_data->assets.GetFont("menu_Font"));
	clockText.setCharacterSize(32);
	clockText.setFillColor(MAIN_BLACK_COLOR);
	clockText.setString("Time: " + _gameClock.getTimeString());
	clockText.setPosition(20, 20);

	_data->window.draw(clockText);
	_data->window.display();
}