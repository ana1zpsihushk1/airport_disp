/*#pragma once

#include <string>
#include <SFML/Graphics.hpp>

class Airport;
enum class StripType 
{ 
    Universal,
    Limitted
};

class Strip
{
public:
    Strip(StripType type, int length);

    StripType getType() const { return type; }
    int getLength() const { return length; }
    sf::Vector2f getSize() const { return shape.getSize(); }
    bool isAvailable() const { return !occupied; }

    void occupy() { occupied = true; }
    void release() { occupied = false; }

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
    sf::Vector2f getEndPosition() const;
    void setSize(sf::Vector2f size);
    void draw(sf::RenderWindow& window);

    Airport* owner = nullptr;
    void setOwner(Airport* a) { owner = a; }
    Airport* getOwner() const { return owner; }
private:
    StripType type;
    int length;
    bool occupied = false;

    sf::RectangleShape shape;
};*/