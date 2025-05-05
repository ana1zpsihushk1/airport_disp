#include <iostream>
#include <memory>

#include "Regional.h"

Regional::Regional(int fuel, int circles, int minus, float speed)
	: fuel(fuel), circles(circles), minus(minus), speed(speed) {}

std::string Regional::getType() const
{
	return "Regional";
}

int Regional::getInitFuel() const
{
	return fuel;
}

int Regional::getMaxCircles() const
{
	return circles;
}
int Regional::getInitMinus() const
{
	return minus;
}

float Regional::getSpeed() const
{
	return speed;
}
