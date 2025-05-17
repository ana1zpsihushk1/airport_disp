#pragma once

#include <iostream>
#include <memory>
#include <vector>

class Airplane;

class Role
{
public:
	virtual ~Role() = default;

	virtual std::string getType() const = 0;
	virtual int getInitFuel() const = 0;
	virtual int getMaxCircles() const = 0;
	virtual int getInitMinus() const = 0;
	virtual float getSpeed() const = 0;
	
	virtual float getTakeoffDuration() const = 0;
	virtual float getLandingDuration() const = 0;

	virtual std::string getCode() const = 0;
};