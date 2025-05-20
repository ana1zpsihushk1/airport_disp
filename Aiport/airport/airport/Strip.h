#pragma once
#include <string>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>
#include "Role.h"

class Airplane;

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

    bool isAvailable() const { return !occupied; }
    bool isAvailableFor(const std::string& typeCode) const;

    void occupy(float timeSeconds = 3.f);       // blocking time
    void release();

    void update(float dt);

    void setPosition(sf::Vector2f pos);
    sf::Vector2f getPosition() const;
    void setSize(sf::Vector2f size);

    void addAllowedType(const std::string typeCode);
    void draw(sf::RenderWindow& window);

    void setTakeoffPath(const std::vector<sf::Vector2f>& path);
    void setLandingPath(const std::vector<sf::Vector2f>& path);
    const std::vector<sf::Vector2f>& getTakeoffPath() const;
    const std::vector<sf::Vector2f>& getLandingPath() const;

    void updateColor();

    void setHighlightColor(const sf::Color& color);

    void reserveUntil(sf::Time time);
    bool isAvailableAt(sf::Time time) const;

    bool canAccept(const Role& role) const;
private:
    StripType type;
    int length;
    bool occupied = false;
    float occupationTimeRemaining = 0.f;

    sf::Time availableUntil;

    std::vector<sf::Vector2f> takeoffPath;
    std::vector<sf::Vector2f> landingPath;

    std::vector<std::string> allowedTypes;
    sf::RectangleShape shape;
};