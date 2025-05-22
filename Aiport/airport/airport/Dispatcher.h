#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include <set>

#include "Engine.h"
#include "Button.h"
#include "inputManager.h"
#include "state.h"
#include "definitions.h"

#include "AirportPlayer.h"
#include "Airplane.h"
#include "Strip.h"
#include "Role.h"
#include "RoleFabric.h"
#include "AirplaneUtils.h"
#include "ParkingRoutes.h"

class Dispatcher
{
public:
	Dispatcher(std::shared_ptr<AirportPlayer> airport, GameDataRef data, sf::Font& font);

	void handleInput(const sf::Vector2i& mousePos);
	void update(float dt);
	void draw(sf::RenderWindow& window);

	std::vector<sf::Vector2f> chooseTakeoffPathByType(const std::string& type);
	std::vector<sf::Vector2f> chooseLandingPathByType(const std::string& type);

	void createPlaneWithSchedule();

	std::vector<sf::Vector2f> assignParking(std::shared_ptr<Airplane> plane);

	void resetGame();
private:
	int level = 0;
	int points = 0;

	int flightCounter = 0;
	const int MAX_FLIGHTS_PER_DAY = 60;
	const int FLIGHT_DAY_DURATION = 43200;

	GameDataRef _data;
	std::shared_ptr<AirportPlayer> _airport;
	std::shared_ptr<Airplane> _selectedPlane;

	std::vector<sf::Text> scheduleTexts;
	
	sf::RectangleShape infoPanel;
	sf::Text titleText;
	Button* exitButton = nullptr;

	std::vector<sf::Text> displayTexts;
	std::vector<std::shared_ptr<Airplane>> displayPlanes;

	std::vector<Button> chooseButtons;
	std::vector<Button> roundButtons;
	std::vector<Button> lineButtons;

	std::set<std::string> createdTypes;

	float nextPlaneUI_YOffset = 70.f;

	std::map<int, bool> smallParkingOccupied;
	std::map<int, bool> bigParkingOccupied;

	void initUI(sf::Font& font);
	void createPlaneUI(std::shared_ptr<Airplane> plane, float yOffset);
	void handleChooseLine(std::shared_ptr<Airplane> plane);
	void selectPlane(const sf::Vector2i& mousePos);
	void issueTakeoff();
	void issueLanding();
};