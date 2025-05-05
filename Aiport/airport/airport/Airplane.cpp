#include <iostream>
#include "Airplane.h"


Airplane::Airplane(std::string id, std::unique_ptr<Role> role)
    : id(std::move(id)), role(std::move(role)),
    fuel(role->getInitFuel()),
    circles(role->getMaxCircles()),
    status(AirplaneStatus::waitTakeoff) 
{
    sprite.setRadius(10.f);
    sprite.setFillColor(sf::Color::Black); //потом цвета менять будем
    sprite.setOrigin(10.f, 10.f); // центр круга
}

void Airplane::tick() //если надо - поправим
{
    updateMovement(); // ПРАВИТЬ СКОРЕЕ ВСЕГО НАДО БУДЕТ
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
    //АНИМАЦИЯ???
}

bool Airplane::requestLanding() //ВЗАИМОДЕЙСТВИЕ С ИГРОКОМ
//БУДЕМ ПРАВИТЬ 
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
    //ТУТ БУДЕТ ПРОВЕРКА НА РАСПИСАНИЕ И ОТВЕТ ДЕСПЕТЧЕРА  
    if (status == AirplaneStatus::waitTakeoff)
    {
        status = AirplaneStatus::takingOff;
        return true;
    }
    return false;
}

//отрисовка
void Airplane::setPosition(sf::Vector2f pos) 
{
    sprite.setPosition(pos);
}

void Airplane::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

void Airplane::startTakeoff(Strip* target)
{
    if (!target || !target->isAvailable()) return;

    currentStrip = target;
    currentStrip->occupy();

    sf::Vector2f stripPos = currentStrip->getPosition();
    taxiTarget = stripPos + sf::Vector2f(20.f, 0.f); // начало полосы (примерно центр)
    sf::Vector2f dir = taxiTarget - sprite.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

    if (len > 0)
    {
        velocity = dir / len * role->getSpeed();
    }
    else
    {
        velocity = { 0.f, 0.f };
    }

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
    targetPosition = stripPos + sf::Vector2f(0.f, length); // разгон вперёд

    sf::Vector2f dir = targetPosition - sprite.getPosition();
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 0)
        velocity = dir / len * role->getSpeed(); // учёт скорости по роли
    else
        velocity = { 0.f, 0.f };*/
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
            // Начать разгон
            sf::Vector2f endPoint = currentStrip->getPosition() + sf::Vector2f(0.f, currentStrip->getLength() * 2);
            sf::Vector2f dir = endPoint - sprite.getPosition();
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            velocity = (len > 0) ? dir / len * role->getSpeed() : sf::Vector2f{ 0.f, 0.f };

            targetPosition = endPoint;
            takeoffProgress = 0.f;
            status = AirplaneStatus::takingOff;
        }
        return;
    }

    if (status == AirplaneStatus::takingOff)
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
}