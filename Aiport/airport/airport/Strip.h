#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

class Airplane;
class Role;

enum class StripType 
{
    CargoOnly,
    LocalOnly,
    NarrowbodyOnly,
    WidebodyOnly,
    RegionalOnly
};

class Strip 
{
public:
    Strip(int id, StripType type);

    bool isAvailableAt(sf::Time time) const;
    bool canAccept(const Role& role) const;

    void reserveUntil(sf::Time time); //бронь
    sf::Time getAvailableTime() const;
    StripType getType() const;
    int getId() const;

    //draw
    void setShapeGeometry(sf::Vector2f size, sf::Vector2f position, sf::Color color);
    void draw(sf::RenderWindow& window) const;

private:
    int id; //need or not? idk
    StripType type;
    sf::Time availableUntil;

    //draw
    sf::RectangleShape shape;
};
