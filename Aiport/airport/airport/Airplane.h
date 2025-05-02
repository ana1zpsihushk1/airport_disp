#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "Role.h"

enum class AirplaneStatus
{
	waitTakeoff, //ожидание взлета
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

private:
	int fuel;
	int circles;

	std::string id;
	std::unique_ptr<Role> role;

	AirplaneStatus status;
};
