#pragma once
#include <string>
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

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

private:
    StripType type;
    int length;
    bool occupied = false;
    float occupationTimeRemaining = 0.f;

    std::vector<std::string> allowedTypes;
    sf::RectangleShape shape;
};