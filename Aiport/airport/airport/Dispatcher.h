#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "AirportPlayer.h"
#include "Airplane.h"
#include "Strip.h"
#include "Role.h"
#include "RoleFabric.h"

#include "inputManager.h"
#include "state.h"
#include "definitions.h"

class Dispatcher
{
public:
	Dispatcher(std::shared_ptr<AirportPlayer> airport);

	void handleInput(const sf::Vector2i& mousePos);
	void update(float dt);
	void draw(sf::RenderWindow& window);
private:
	int level;
	int points;

	std::shared_ptr<AirportPlayer> _airport;
	std::shared_ptr<Airplane> _selectedPlane;

	void selectPlane(const sf::Vector2i& mousePos);
	void issueTakeoff();
	void issueLanding();
};