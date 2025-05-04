#pragma once
#include <SFML/System.hpp>
#include <iostream>
#include <memory>

#include "Role.h"
#include "Airplane.h"

class Regional : public Role
{
public:
	Regional(int fuel, int circles);
	std::string getType() const override;
	int getInitFuel() const override;
	int getMaxCircles() const override;
private:
	int fuel; //откалибровать
	int circles; //откалибровать
};