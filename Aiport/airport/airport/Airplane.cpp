#include <iostream>
#include "Airplane.h"
#include "Airport.h"

Airplane::Airplane(std::string id, std::unique_ptr<Role> role)
    : id(std::move(id)), role(std::move(role)),
    fuel(role->getInitFuel()),
    circles(role->getMaxCircles()),
    status(AirplaneStatus::waitTakeoff),
    hasStartedFlight(false)
{
    sprite.setRadius(10.f);
    sprite.setFillColor(sf::Color::Black); //потом цвета менять будем
    sprite.setOrigin(10.f, 10.f); // центр круга
}

void Airplane::crash()
{
    status = AirplaneStatus::crashed;
    //АНИМАЦИЯ???
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
            dot.setFillColor(sf::Color(150, 150, 150)); // серый пунктир
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

//ДАВАЙ ПО НОВОЙ САНЯ

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
    case AirplaneStatus::inSky:
        updateFlight();
        break;
    case AirplaneStatus::landing:
        // пока просто остановка
        velocity = { 0.f, 0.f };
        break;
    default:
        break;
    }

    if (status == AirplaneStatus::inSky)
    {
        fuel--;
        if (fuel <= 0)
            crash();
    }
}



// VZLET
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
    float distanceToEnd = std::sqrt(std::pow(stripEndPos.x - sprite.getPosition().x, 2) +
        std::pow(stripEndPos.y - sprite.getPosition().y, 2));
    float step = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    if (distanceToEnd <= step)
    {
        sprite.setPosition(stripEndPos);
        velocity = { 0.f, 0.f };
        currentStrip->release();
        status = AirplaneStatus::inSky;
        Strip* destStrip = destinationAirport->findSuitableStrip(role->getType());
        if (destStrip) {
            startFlight(destStrip);
        }
        return;
    }
    else
    {
        sprite.move(velocity);
    }
}

sf::Vector2f Airplane::normalize(sf::Vector2f v)
{
    float len = std::sqrt(v.x * v.x + v.y * v.y);
    return (len != 0) ? v / len : sf::Vector2f(0, 0);
}

bool Airplane::reached(sf::Vector2f target)
{
    float dist = std::sqrt(std::pow(target.x - sprite.getPosition().x, 2) +
        std::pow(target.y - sprite.getPosition().y, 2));
    return dist <= role->getSpeed(); 
}

// POLET (I BELIEVE I CAN FLY)
void Airplane::setDestinationAirport(Airport* airport)
{
    destinationAirport = airport;
}

void Airplane::startFlight(Strip* targetStrip)
{
    if (!targetStrip) return;

    currentStrip = targetStrip;
    currentStrip->occupy();

    flightStart = sprite.getPosition();
    flightEnd = targetStrip->getEndPosition(); // ДАЛЬНИЙ конец полосы

    // случайная точка управления (в центре + смещение)
    sf::Vector2f center = (flightStart + flightEnd) / 2.f;
    float offsetX = std::rand() % 200 - 100;
    float offsetY = std::rand() % 150 - 75;
    flightBezierControl = center + sf::Vector2f(offsetX, offsetY);

    // длительность полёта ПОМЕНЯЕМ ЕСЛИ НАДО - ТУТ РАСПИСАНИЕ ВТУПАЕТ В СИЛУ
    std::string type = role->getType();
    if (type == "WideBody" || type == "Cargo") flightDuration = 300.f;
    else if (type == "NarrowBody") flightDuration = 220.f;
    else if (type == "Regional") flightDuration = 150.f;
    else flightDuration = 100.f;

    flightTimer = 0.f;
}

void Airplane::updateFlight()
{
    if (status != AirplaneStatus::inSky) return;

    flightTimer += 1.f;
    fuel--;

    float t = flightTimer / flightDuration;
    if (t >= 1.f)
    {
        // завершить полёт, перейти к посадке
        sprite.setPosition(flightEnd);
        currentStrip->release();
        velocity = { 0.f, 0.f };
        status = AirplaneStatus::landing; // посадка - ПОЗЖЕ
        trail.clear();
        return;
    }
    // кривая Безье
    sf::Vector2f P0 = flightStart;
    sf::Vector2f P1 = flightBezierControl;
    sf::Vector2f P2 = flightEnd;

    sf::Vector2f pos = (1 - t) * (1 - t) * P0 + 2 * (1 - t) * t * P1 + t * t * P2;
    sprite.setPosition(pos);

    // след
    if ((int)flightTimer % 4 == 0)
    {
        trail.push_back(pos);
        if (trail.size() > 60) trail.pop_front();
    }
    if (fuel <= 0)
    {
        crash(); //GAME OVER
    }
}