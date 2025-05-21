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
private:
	int level = 0;
	int points = 0;

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

	void initUI(sf::Font& font);
	void createPlaneUI(std::shared_ptr<Airplane> plane);
	void handleChooseLine(std::shared_ptr<Airplane> plane);
	void selectPlane(const sf::Vector2i& mousePos);
	void issueTakeoff();
	void issueLanding();
};