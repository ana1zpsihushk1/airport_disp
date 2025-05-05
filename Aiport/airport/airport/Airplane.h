#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

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

	void setPosition(sf::Vector2f pos);
	//void moveTo(sf::Vector2f targetPos);
	void startTakeoff(Strip* targetStrip); // основная логика взлёта
	void updateMovement();                 // вызывается каждый тик
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
