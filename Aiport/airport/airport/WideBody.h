#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Role.h"
#include "Airplane.h"

class WideBody : public Role
{
public:
	WideBody(int fuel = 100, int circles = 3, int minus = 5, float speed = 0.1f);
	std::string getType() const override;
	int getInitFuel() const override;
	int getMaxCircles() const override;
	int getInitMinus() const override;
	float getSpeed() const override;
private:
	int fuel;
	int circles;
	int minus;
	float speed;
};