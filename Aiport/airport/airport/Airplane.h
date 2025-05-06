#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>
#include <deque>

#include "Role.h"
#include "Strip.h"

enum class AirplaneStatus
{
	waitTakeoff, //ожидание взлета
	taxiingToStrip, //агрессивно подъезжаем к ВПП
	takingOff, //взлет
	inSky, //летит (в небе)
	landing, //приземление
	landedMove, // едет по земле
	crashed // крушение
};


class Airplane
{
public:
	Airplane(std::string id, std::unique_ptr<Role> role);

	void tick(); // игровой шаг, пока там потеря топлива
	void crash();

    //функции взаимодействия с игроком
    bool requestLanding();
    bool requestTakingOff();

    const std::string& getId() const { return id; };
    int getFuel() const { return fuel; };
    AirplaneStatus getStatus() const { return status; };
    std::string getTypeName() const { return role->getType(); };

	void setFromNpc(bool val) { fromNpc = val; }
	void setPosition(sf::Vector2f pos);
	void startTakeoff(Strip* targetStrip, bool isPlayer); // взлёт
	void updateMovement();                 // вызывается каждый тик
	void draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const;
	void startFlight(sf::Vector2f target); // запуск полёта
	void updateFlight();                   // вызывается каждый тик
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
	sf::Vector2f targetPosition;
	sf::Vector2f taxiTarget;
	float takeoffProgress = 0.f;
	float takeoffDistance = 0.f;
	Strip* currentStrip = nullptr;

	float flightDuration = 0.f;
	float flightTimer = 0.f;
	sf::Vector2f flightTarget;
	sf::Vector2f flightStart;
	sf::Vector2f flightControlPoint; 
	std::deque<sf::Vector2f> trail; // пунктир
};
