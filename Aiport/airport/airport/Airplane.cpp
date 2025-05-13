#include <iostream>
#include "Airplane.h"


Airplane::Airplane(std::string id, std::unique_ptr<Role> role)
    : id(std::move(id)), role(std::move(role)),
    fuel(role->getInitFuel()),
    circles(role->getMaxCircles()),
    status(AirplaneStatus::waitTakeoff),
    hasStartedFlight(false)
{
    sprite.setRadius(10.f);
    sprite.setFillColor(sf::Color::Black); //ïîòîì öâåòà ìåíÿòü áóäåì
    sprite.setOrigin(10.f, 10.f); // öåíòğ êğóãà
}

void Airplane::crash()
{
    status = AirplaneStatus::crashed;
    //ÀÍÈÌÀÖÈß???
}

void Airplane::setPosition(sf::Vector2f pos) 
{
    sprite.setPosition(pos);
}
void Airplane::setParkPosition(sf::Vector2f pos) 
{
    parkPosition = pos;
}

void Airplane::draw(sf::RenderWindow& window)
{
    if (status == AirplaneStatus::inSky && !trail.empty())
    {
        for (const auto& point : trail)
        {
            sf::CircleShape dot(2.f);
            dot.setFillColor(sf::Color(150, 150, 150)); // ñåğûé ïóíêòèğ
            dot.setOrigin(1.f, 1.f);
            dot.setPosition(point);
            window.draw(dot);
        }
    }
    window.draw(sprite);
}


sf::Vector2f Airplane::getPosition() const
{
    return sprite.getPosition();
}

//ÄÀÂÀÉ ÏÎ ÍÎÂÎÉ ÑÀÍß

void Airplane::tick()
{
    switch (status)
    {
    case AirplaneStatus::movingToStrip:
        moveToStripStart();
        break;
    case AirplaneStatus::takingOff:
        moveAlongStrip();
        break;
        //ÎÑÒÀËÜÍÎÅ ÏÎÇÆÅ
    default:
        break;
    }
}

void Airplane::startMoveToStrip(Strip* strip)
{
    currentStrip = strip;
    currentStrip->occupy();

    stripStartPos = strip->getPosition();
    //stripEndPos = stripStartPos - sf::Vector2f(0.f, strip->getLength());
    stripEndPos = stripStartPos + sf::Vector2f(0.f, strip->getSize().y);

    velocity = normalize(stripStartPos - parkPosition) * role->getSpeed();
    sprite.setPosition(parkPosition);
    status = AirplaneStatus::movingToStrip;
}

void Airplane::moveToStripStart()
{
    if (reached(stripStartPos)) 
    {
        sprite.setPosition(stripStartPos);
        velocity = normalize(stripEndPos - stripStartPos) * role->getSpeed();
        status = AirplaneStatus::takingOff;
    }
    else 
    {
        sprite.move(velocity);
    }
}

void Airplane::moveAlongStrip()
{
    if (reached(stripEndPos)) 
    {
        sprite.setPosition(stripEndPos);
        currentStrip->release();
        velocity = { 0.f, 0.f };
        status = AirplaneStatus::inSky; // ïîòîì ÏÒÈ×ÊÀ ÂÛËÅÒÅËÀ
        return; //ËÅÒÈÌ...(ÍÀÄÅŞÑÜ)
    }
    sprite.move(velocity);
}

sf::Vector2f Airplane::normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    return (len != 0) ? v / len : sf::Vector2f(0, 0);
}

bool Airplane::reached(sf::Vector2f target)
{
    sf::Vector2f dir = target - sprite.getPosition();
    sf::Vector2f moveDir = normalize(velocity);

    return (dir.x * moveDir.x + dir.y * moveDir.y) <= 0;
}