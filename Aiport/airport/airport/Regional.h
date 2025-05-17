#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Role.h"
#include "Airplane.h"

class Regional : public Role
{
public:
	Regional(int fuel = 60, int circles = 2, int minus = 3, float speed = 0.1f);
	std::string getType() const override;
	int getInitFuel() const override;
	int getMaxCircles() const override;
	int getInitMinus() const override;
	float getSpeed() const override;

	float getTakeoffDuration() const override { return 6.0f; }
	float getLandingDuration() const override { return 7.0f; }

	std::string getCode() const override { return "RG"; }

private:
	int fuel;
	int circles;
	int minus;
	float speed;
};