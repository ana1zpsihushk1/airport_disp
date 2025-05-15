#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <deque>

#include "Role.h"
#include "Strip.h"

class Airport;

enum class AirplaneStatus
{
	waitTakeoff, //ожидание взлета
	movingToStrip,     // движение к началу ВПП
	takingOff,         // движение по ВПП - взлет
	inSky, //летит (в небе)
	landing, //приземление
	crashed // крушение
};


class Airplane
{
public:
	Airplane(std::string id, std::unique_ptr<Role> role);

	void crash();

    const std::string& getId() const { return id; };
    int getFuel() const { return fuel; };
    AirplaneStatus getStatus() const { return status; };
    std::string getTypeName() const { return role->getType(); };

	void setFromNpc(bool val) { fromNpc = val; }
	void setPosition(sf::Vector2f pos);
	void setParkPosition(sf::Vector2f pos);
	void draw(sf::RenderWindow& window);
	sf::Vector2f getPosition() const;

	//ДАВАЙ ПО НОВОЙ САНЯ
	void tick(); // игровой шаг

	//VZLET
	void startMoveToStrip(Strip* strip);
	void moveToStripStart();
	void moveAlongStrip();

	sf::Vector2f normalize(sf::Vector2f v);
	bool reached(sf::Vector2f target);

	//POLET
	void startFlight(Strip* targetStrip); // задаём путь
	void updateFlight(); // вызывается каждый тик - топливо теряем
	void setDestinationAirport(Airport* airport);




private:
	int fuel;
	int circles;

	std::string id;
	std::unique_ptr<Role> role;

	AirplaneStatus status;

	bool fromNpc = false;
	bool hasStartedFlight = false;

	sf::CircleShape sprite;             
	sf::Vector2f velocity = { 0.f, 0.f }; 
	Strip* currentStrip = nullptr;

	//ПО НОВОЙ
	sf::Vector2f parkPosition;
	sf::Vector2f stripStartPos;
	sf::Vector2f stripEndPos;
	std::deque<sf::Vector2f> trail;

	float flightTimeRemaining = 0.f;
	float flightDuration = 0.f;
	float flightTimer = 0.f;

	sf::Vector2f flightStart;
	sf::Vector2f flightEnd;
	sf::Vector2f flightBezierControl;

	Airport* destinationAirport = nullptr;
};
