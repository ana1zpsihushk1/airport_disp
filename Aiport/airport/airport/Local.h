#pragma once

#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Role.h"
#include "Airplane.h"

class Local : public Role
{
public:
	Local(int fuel = 40, int circles = 1, int minus = 2, float speed = 0.1f);
	std::string getType() const override;
	int getInitFuel() const override;
	int getMaxCircles() const override;
	int getInitMinus() const override;
	float getSpeed() const override;

	float getTakeoffDuration() const override { return 3.0f; }
	float getLandingDuration() const override { return 4.0f; }

	std::string getCode() const override { return "LC"; }

private:
	int fuel;
	int circles;
	int minus;
	float speed;
};