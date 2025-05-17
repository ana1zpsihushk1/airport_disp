#include <iostream>
#include <random>
#include <sstream>
#include <cmath>

#include "Airplane.h"
#include "AirplaneUtils.h"

static std::string generatePlaneName(const std::string& code)
{
    std::ostringstream oss;
    oss << code << "-";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 9);
    for (int i = 0; i < 4; ++i)
        oss << dis(gen);
    return oss.str();
}

Airplane::Airplane(std::string id, std::unique_ptr<Role> rolePtr, const sf::Font& font)
    : id(std::move(id)), role(std::move(rolePtr)), fuel(role->getInitFuel()), circles(role->getMaxCircles()), status(AirplaneStatus::waitTakeoff)
{
    sprite.setRadius(10.f);
    sprite.setFillColor(sf::Color::Black);
    sprite.setOrigin(10.f, 10.f);

    name = generatePlaneName(role->getCode());

    takeoffDuration = role->getTakeoffDuration();
    landingDuration = role->getLandingDuration();

    nameText.setFont(font);
    nameText.setString(name);
    nameText.setCharacterSize(14);
    nameText.setFillColor(sf::Color::White);

    sf::FloatRect bounds = nameText.getLocalBounds();
    nameBackground.setSize({ bounds.width + 10.f, bounds.height + 6.f });
    nameBackground.setFillColor(sf::Color(100, 100, 100, 180));
    nameBackground.setOrigin(nameBackground.getSize().x / 2.f, nameBackground.getSize().y);
}

void Airplane::tick() //maybe we will fix it
{
    updateMovement(); // WE NEED TO FIX IT
    if ((status == AirplaneStatus::inSky) || (status == AirplaneStatus::takingOff)
        || (status == AirplaneStatus::landing))
    {
        fuel--;
        if (fuel <= 0)
        {
            crash();
        }
    }
}

void Airplane::crash()
{
    status = AirplaneStatus::crashed;
    // animation???
}

bool Airplane::requestLanding() // interaction with player
// we are going to fix it
{
    if (circles > 0)
    {
        circles--;
        return false;
    }
    else
    {
        status = AirplaneStatus::landing;
        return true;
    }
}

bool Airplane::requestTakingOff()
{
    // it will be test of schedule and answer from dispatcher
    if (status == AirplaneStatus::waitTakeoff)
    {
        status = AirplaneStatus::takingOff;
        return true;
    }
    return false;
}

void Airplane::setPosition(sf::Vector2f pos)
{
    sprite.setPosition(pos);
    nameText.setPosition(pos.x, pos.y - 20.f);
    nameBackground.setPosition(pos.x, pos.y - 20.f);
}

void Airplane::draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    nameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 18.f);
    nameBackground.setPosition(nameText.getPosition());

    window.draw(nameBackground);
    window.draw(nameText);
}

void Airplane::startTakeoff(Strip* target)
{
    if (!target || !target->isAvailable()) return;

    currentStrip = target;
    currentStrip->occupy();

    sf::Vector2f stripPos = currentStrip->getPosition();
    taxiTarget = stripPos + sf::Vector2f(20.f, 0.f);

    sf::Vector2f dir = taxiTarget - sprite.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len > 0)
        velocity = dir / len * role->getSpeed();
    else
        velocity = sf::Vector2f{ 0.f, 0.f };

    status = AirplaneStatus::taxiingToStrip;

    /*if (!target || !target->isAvailable())
    {
        return;
    }
    currentStrip = target;
    currentStrip->occupy();

    status = AirplaneStatus::takingOff;
    takeoffProgress = 0.f;
    sf::Vector2f stripPos = currentStrip->getPosition();
    float length = static_cast<float>(currentStrip->getLength() * 2);
    targetPosition = stripPos + sf::Vector2f(0.f, length); // ðàçãîí âïåð¸ä

    sf::Vector2f dir = targetPosition - sprite.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 0)
        velocity = dir / len * role->getSpeed(); // ó÷¸ò ñêîðîñòè ïî ðîëè
    else
        velocity = { 0.f, 0.f };
    */
}

void Airplane::updateMovement()
{
    if (status == AirplaneStatus::taxiingToStrip)
    {
        sprite.move(velocity);

        sf::Vector2f pos = sprite.getPosition();
        float dx = pos.x - taxiTarget.x;
        float dy = pos.y - taxiTarget.y;

        if (std::sqrt(dx * dx + dy * dy) < 2.0f)
        {
            // start of taking off
            sf::Vector2f endPoint = currentStrip->getPosition() + sf::Vector2f(0.f, currentStrip->getLength() * 2);
            sf::Vector2f dir = endPoint - sprite.getPosition();
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            velocity = (len > 0) ? dir / len * role->getSpeed() : sf::Vector2f{ 0.f, 0.f };

            targetPosition = endPoint;
            takeoffProgress = 0.f;
            status = AirplaneStatus::takingOff;
        }
        //return;
    }

    else if (status == AirplaneStatus::takingOff)
    {
        sprite.move(velocity);
        takeoffProgress += std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
        if (takeoffProgress >= currentStrip->getLength() * 2)
        {
            currentStrip->release();
            velocity = { 0.f, 0.f };
            status = AirplaneStatus::inSky;
        }
    }
    /*if (status != AirplaneStatus::takingOff)
    {
        return;
    }
    sprite.move(velocity);
    takeoffProgress += std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    if (takeoffProgress >= currentStrip->getLength() * 2)
    {
        currentStrip->release();
        velocity = { 0.f, 0.f };
        status = AirplaneStatus::inSky;
    }*/

    nameText.setPosition(sprite.getPosition().x, sprite.getPosition().y - 20.f);
    nameBackground.setPosition(sprite.getPosition().x, sprite.getPosition().y - 20.f);
}

void Airplane::setSchedule(const FlightSchedule& schedule)
{
    _schedule = schedule;
}

FlightSchedule Airplane::getSchedule() const
{
    return _schedule;
}
