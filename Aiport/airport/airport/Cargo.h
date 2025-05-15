#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Role.h"
#include "Airplane.h"

class Cargo : public Role
{
public:
	Cargo(int fuel = 10000, int circles = 3, int minus = 5, float speed = 2.0f);
	std::string getType() const override;
	int getInitFuel() const override;
	int getMaxCircles() const override;
	int getInitMinus() const override;
	float getSpeed() const override;
private:
	int fuel; //откалибровать
	int circles; //откалибровать
	int minus;
	float speed;
};