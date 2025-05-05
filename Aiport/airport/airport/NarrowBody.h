#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Role.h"
#include "Airplane.h"

class NarrowBody : public Role
{
public:
	NarrowBody(int fuel, int circles, int minus);
	std::string getType() const override;
	int getInitFuel() const override;
	int getMaxCircles() const override;
	int getInitMinus() const override;
private:
	int fuel; //откалибровать
	int circles; //откалибровать
	int minus;
};