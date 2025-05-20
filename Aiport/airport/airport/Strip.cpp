#include "definitions.h"

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
    updateColor();
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

void Strip::setTakeoffPath(const std::vector<sf::Vector2f>& path)
{
    takeoffPath = path;
}

void Strip::setLandingPath(const std::vector<sf::Vector2f>& path)
{
    landingPath = path;
}

const std::vector<sf::Vector2f>& Strip::getTakeoffPath() const
{
    return takeoffPath;
}

const std::vector<sf::Vector2f>& Strip::getLandingPath() const
{
    return landingPath;
}

void Strip::updateColor()
{
    if (occupied)
        shape.setFillColor(BUTTON_MAIN_RED_COLOR);

    else
        shape.setFillColor(BUTTON_MAIN_COLOR);
}

void Strip::setHighlightColor(const sf::Color& color)
{
    shape.setFillColor(color);
}

void Strip::reserveUntil(sf::Time time)
{
    availableUntil = time;
}

bool Strip::isAvailableAt(sf::Time time) const
{
    return time >= availableUntil;
}

bool Strip::canAccept(const Role& role) const
{
    std::string roleType = role.getType();

    return std::find(allowedTypes.begin(), allowedTypes.end(), roleType) != allowedTypes.end();
}
