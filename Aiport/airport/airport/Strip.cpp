#include "Strip.h"
#include "Role.h"

Strip::Strip(int id, StripType type)
    : id(id), type(type), availableUntil(sf::Time::Zero) {}

bool Strip::isAvailableAt(sf::Time time) const 
{
    return time >= availableUntil;
}

bool Strip::canAccept(const Role& role) const 
{
    std::string rType = role.getType();

    switch (type) 
    {
    case StripType::CargoOnly:
        return rType == "Cargo";
    case StripType::LocalOnly:
        return rType == "Local";
    case StripType::NarrowbodyOnly:
        return rType == "NarrowBody";
    case StripType::WidebodyOnly:
        return rType == "WideBody";
    case StripType::RegionalOnly:
        return rType == "Regional";
    default:
        return false;
    }
}

void Strip::reserveUntil(sf::Time time)  //ZANYATO
{
    availableUntil = time;
}

sf::Time Strip::getAvailableTime() const 
{
    return availableUntil;
}

StripType Strip::getType() const 
{
    return type;
}

int Strip::getId() const 
{
    return id;
}

//draw
void Strip::setShapeGeometry(sf::Vector2f size, sf::Vector2f position, sf::Color color) 
{
    shape.setSize(size);
    shape.setPosition(position);
    shape.setFillColor(color);
}

void Strip::draw(sf::RenderWindow& window) const 
{
    window.draw(shape);
}