#include "simulationState1.h"
#include "definitions.h"
#include "menuState.h"

simulationState1::simulationState1(GameDataRef data) : _data(data) {}

void simulationState1::Init()
{
	const int windowWidth = SCREEN_WIDTH;
	const int windowHeight = SCREEN_HEIGHT;

	sf::Vector2f airportSize(300, 200);
	sf::Vector2f playerPos(windowWidth - airportSize.x - 20, 20);
	sf::Vector2f npcPos(20, windowHeight - airportSize.y - 20);

	AirPlayer = std::make_shared<AirportPlayer>(playerPos, airportSize);
	AirNpc = std::make_shared<AirportNpc>(npcPos, airportSize);
	AirPlayer->initStrip();
	AirNpc->initStrip();

	auto plane = std::make_shared<Airplane>("Plane_" + std::to_string(planeId++), createRandomRole());
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
	}
}

void simulationState1::Update(float dt)
{
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
	_data->window.clear(sf::Color::White);

	AirPlayer->draw(_data->window);
	AirNpc->draw(_data->window);

	for (auto& p : activePlanes)
	{
		p->draw(_data->window);
	}

	_data->window.display();
}