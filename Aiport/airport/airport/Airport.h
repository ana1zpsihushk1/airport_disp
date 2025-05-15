#pragma once

#include <vector>
#include <memory>

#include "Airplane.h"

class Airport
{
public:
	virtual void tick(float dt) = 0;
	virtual void acceptAirplane(std::shared_ptr<Airplane> plane) = 0;
	virtual Strip* findSuitableStrip(const std::string& typeName) = 0;
	virtual ~Airport() = default;
	void setOppositeAirport(Airport* airport) { oppositeAirport = airport; }
	Airport* getOppositeAirport() const { return oppositeAirport; }
protected:
	Airport* oppositeAirport = nullptr;
};