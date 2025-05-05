#include <iostream>
#include <memory>

#include "Cargo.h"

Cargo::Cargo(int fuel, int circles, int minus, float speed)
	: fuel(fuel), circles(circles), minus(minus), speed(speed) {}

std::string Cargo::getType() const
{
	return "Cargo";
}

int Cargo::getInitFuel() const
{
	return fuel;
}

int Cargo::getMaxCircles() const
{
	return circles;
}

int Cargo::getInitMinus() const
{
	return minus;
}

float Cargo::getSpeed() const
{
	return speed;
}
