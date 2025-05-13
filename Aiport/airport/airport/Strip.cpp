#include "Strip.h"

Strip::Strip(StripType type, int length) : 
	type(type), length(length) 
{
    shape.setSize(sf::Vector2f(40.f, static_cast<float>(length)));
    shape.setFillColor(type == StripType::Universal ? sf::Color::Green : sf::Color(150, 75, 0));
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

void Strip::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}