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


private:
	int fuel;
	int circles;

	std::string id;
	unique_ptr<Role> role;

	AirplaneStatus status;
};