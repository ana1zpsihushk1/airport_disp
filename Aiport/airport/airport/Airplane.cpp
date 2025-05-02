#include "Airplane.h"
#include <iostream>

Airplane::Airplane(std::string id, std::unique_ptr<Role> role)
    : id(std::move(id)), role(std::move(role)),
    fuel(role->getInitFuel()),
    holdingCirclesLeft(role->maxCircles()),
    status(AirplaneStatus::waitTakeoff) {}