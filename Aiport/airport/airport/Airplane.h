#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "Role.h"
#include "Strip.h"

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
	Airplane(std::string id, std::unique_ptr<Role> role);

	void tick(); // èãðîâîé øàã, ïîêà òàì ïîòåðÿ òîïëèâà
	void crash();

	//ôóíêöèè âçàèìîäåéñòâèÿ ñ èãðîêîì
	bool requestLanding();
	bool requestTakingOff();

	const std::string& getId() const { return id; };
	int getFuel() const { return fuel; };
	AirplaneStatus getStatus() const { return status; };
	std::string getTypeName() const { return role->getType(); };

	void setPosition(sf::Vector2f pos);
	//void moveTo(sf::Vector2f targetPos);
	void startTakeoff(Strip* targetStrip); // îñíîâíàÿ ëîãèêà âçë¸òà
	void updateMovement();                 // âûçûâàåòñÿ êàæäûé òèê
	void draw(sf::RenderWindow& window);

private:
	int fuel;
	int circles;

	std::string id;
	std::unique_ptr<Role> role;

	AirplaneStatus status;

	sf::CircleShape sprite;
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f targetPosition;
	sf::Vector2f taxiTarget;
	float takeoffProgress = 0.f;
	Strip* currentStrip = nullptr;
};