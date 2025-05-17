#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "definitions.h"
#include "Role.h"
#include "Strip.h"
#include "FlightSchedule.h"

enum class AirplaneStatus
{
	waitTakeoff,
	taxiingToStrip,
	takingOff,
	inSky,
	landing, 
	landedMove,
	crashed
};


class Airplane
{
public:
	Airplane(std::string id, std::unique_ptr<Role> role, const sf::Font& font);

	void tick(); // playing step (it`s just losing of fuel now)
	void crash();

	//fuctions for player
	bool requestLanding();
	bool requestTakingOff();

	const std::string& getId() const { return id; };
	int getFuel() const { return fuel; };
	AirplaneStatus getStatus() const { return status; };
	std::string getTypeName() const { return role->getType(); };

	void setPosition(sf::Vector2f pos);
	//void moveTo(sf::Vector2f targetPos);
	void startTakeoff(Strip* targetStrip); // main logic of taking off
	void updateMovement();                 // update tick

	void setSchedule(const FlightSchedule& schedule);
	FlightSchedule getSchedule() const;

	void draw(sf::RenderWindow& window);

private:
	int fuel;
	int circles;

	std::string name;
	sf::Text nameText;
	sf::RectangleShape nameBackground;

	FlightSchedule _schedule;

	std::string id;
	std::unique_ptr<Role> role;

	AirplaneStatus status;

	sf::CircleShape sprite;
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f targetPosition;
	sf::Vector2f taxiTarget;
	float takeoffProgress = 0.f;
	Strip* currentStrip = nullptr;

	float takeoffDuration = 0.f;
	float landingDuration = 0.f;
};