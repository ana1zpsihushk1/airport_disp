#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Role.h"
#include "Airplane.h"

class NarrowBody : public Role
{
public:
	NarrowBody(int fuel = 80, int circles = 2, int minus = 4, float speed = 0.1f);
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