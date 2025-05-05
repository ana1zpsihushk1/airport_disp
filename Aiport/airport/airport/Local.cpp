#include <iostream>
#include <memory>

#include "Local.h"

Local::Local(int fuel = 40, int circles = 1, int minus = 2)
	: fuel(fuel), circles(circles), minus(minus) {}

std::string Local::getType() const
{
	return "Local";
}

int Local::getInitFuel() const
{
	return fuel;
}

int Local::getMaxCircles() const
{
	return circles;
}
int Local::getInitMinus() const
{
	return minus;
}
