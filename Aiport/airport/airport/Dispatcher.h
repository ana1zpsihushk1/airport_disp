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

	int stripIndex(const std::shared_ptr<Strip>& strip);

	void spawnIncomingPlanes();

	void handleLandingAcceptance(std::shared_ptr<Airplane> plane);
private:
	int level = 0;
	int points = 0;

	int currentLevel = 0;
	const int maxLevel = 5;

	std::vector<std::string> types = { "Local", "Regional", "NarrowBody", "Cargo", "WideBody" };

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

	float nextPlaneUI_YOffset = 70.f;

	std::map<int, bool> smallParkingOccupied;
	std::map<int, bool> bigParkingOccupied;

	std::map<std::string, float> chooseLineOffsets;


	std::vector<std::shared_ptr<Airplane>> departurePlanes;
	std::vector<sf::Text> planeButtons;
	std::map<std::string, float> planeButtonYOffsets;
	std::shared_ptr<Airplane> selectedPlane;

	std::vector<std::pair<Button, std::shared_ptr<Strip>>> lineButtons;
	std::map<std::shared_ptr<Strip>, sf::Text> stripLabels;

	std::vector<std::shared_ptr<Airplane>> pendingLandingPlanes;
	std::vector<Button> acceptLandingButtons;

	int acceptedLandingCount = 0;
	int maxLandingRequests = rand() % 3 + 4;
	float nextLandingRequestTime = 0.f;

	void initUI(sf::Font& font);
	void createPlaneUI(std::shared_ptr<Airplane> plane, float yOffset);
	void handleChooseLine(std::shared_ptr<Airplane> plane, float yOffset);
	void selectPlane(const sf::Vector2i& mousePos);
	void issueTakeoff();
	void issueLanding();
};