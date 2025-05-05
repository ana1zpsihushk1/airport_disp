#pragma once

#include <vector>
#include <memory>

#include "Airplane.h"

class Airport
{
public:
	virtual void tick() = 0;
	virtual void acceptAirplane(std::shared_ptr<Airplane> plane) = 0;
	virtual ~Airport() = default;
};