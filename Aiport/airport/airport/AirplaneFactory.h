#pragma once

#include <memory>

#include "Airplane.h"
#include "RoleFabric.h"
#include "FlightSchedule.h"

class AirplaneFactory
{
public:
    static std::shared_ptr<Airplane> createAirplane(const std::string& id, const FlightSchedule& schedule);
};