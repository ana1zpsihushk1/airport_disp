#include "Strip.h"

Strip::Strip(StripType type, int length) :
    type(type), length(length)
{
    shape.setSize(sf::Vector2f(40.f, static_cast<float>(length * 2)));
    shape.setFillColor(type == StripType::Universal ? sf::Color::Green : sf::Color::Red);
}

bool Strip::isAvailableFor(const std::string& typeCode) const
{
    if (!isAvailable())
        return false;

    if (type == StripType::Universal)
        return true;

    return std::find(allowedTypes.begin(), allowedTypes.end(), typeCode) != allowedTypes.end();
}

void Strip::occupy(float timeSeconds)
{
    occupied = true;
    occupationTimeRemaining = timeSeconds;
}

void Strip::release()
{
    occupied = false;
    occupationTimeRemaining = 0.f;
}

void Strip::update(float dt)
{
    if (occupationTimeRemaining > 0.f)
    {
        occupationTimeRemaining -= dt;
        if (occupationTimeRemaining <= 0.f)
        {
            release();
        }
    }
}

void Strip::setPosition(sf::Vector2f pos)
{
    shape.setPosition(pos);
}

sf::Vector2f Strip::getPosition() const
{
    return shape.getPosition();
}

void Strip::setSize(sf::Vector2f size)
{
    shape.setSize(size);
}

void Strip::addAllowedType(const std::string typeCode)
{
    allowedTypes.push_back(typeCode);
}

void Strip::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}