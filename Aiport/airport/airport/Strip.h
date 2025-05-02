#pragma once

#include <string>
#include <SFML/Graphics.hpp>

enum class StripType 
{ 
    Passenger, 
    Cargo 
};

class Strip
{
public:
    Strip(StripType type, int length);

    StripType getType() const { return type; }
    int getLength() const { return length; }
    bool isAvailable() const { return !occupied; }

    void occupy() { occupied = true; }
    void release() { occupied = false; }

    void setPosition(sf::Vector2f pos);
    void setSize(sf::Vector2f size);
    void draw(sf::RenderWindow& window);
private:
    StripType type;
    int length;
    bool occupied = false;

    sf::RectangleShape shape;
};