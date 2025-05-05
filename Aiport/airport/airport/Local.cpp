#include <iostream>
#include <memory>

#include "Local.h"

Local::Local(int fuel, int circles, int minus, float speed)
	: fuel(fuel), circles(circles), minus(minus), speed(speed) {}

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

float Local::getSpeed() const
{
	return speed;
}
