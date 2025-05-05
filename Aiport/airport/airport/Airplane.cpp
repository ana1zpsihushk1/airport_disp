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
    updateFlight();
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
    if (status == AirplaneStatus::inSky) 
    {
        for (auto& point : trail) 
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

void Airplane::startTakeoff(Strip* target, bool isPlayer)
{
    if (!target || !target->isAvailable()) return;

    currentStrip = target;
    currentStrip->occupy();
    status = AirplaneStatus::takingOff;
    takeoffProgress = 0.f;

    sf::Vector2f start = currentStrip->getPosition();
    sf::Vector2f end;

    // направление зависит от типа аэропорта
    if (isPlayer) {
        // Полоса направлена вниз
        end = start + sf::Vector2f(0.f, currentStrip->getLength());
    }
    else {
        // Полоса направлена вверх
        end = start - sf::Vector2f(0.f, currentStrip->getLength());
    }

    sprite.setPosition(start);
    targetPosition = end;

    sf::Vector2f dir = end - start;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    velocity = (len > 0) ? dir / len * role->getSpeed() : sf::Vector2f(0.f, 0.f);
}

void Airplane::updateMovement() 
{
    if (status != AirplaneStatus::takingOff)
        return;

    sprite.move(velocity);
    takeoffProgress += std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    // Расстояние до цели
    sf::Vector2f delta = targetPosition - sprite.getPosition();
    float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);

    if (dist < 1.0f)
    {
        sprite.setPosition(targetPosition);
        currentStrip->release();
        velocity = { 0.f, 0.f };
        status = AirplaneStatus::inSky;

        if (fromNpc)  // самолёт NPC — запускаем полёт
        // для самолета игрока проверка на расписание и разрешение на вылет
        {
            sf::Vector2f flightTarget = (sprite.getPosition().y < 400)
                ? sf::Vector2f(100, 600)       // Игрок - NPC
                : sf::Vector2f(1150, 100);     // NPC - игрок
            startFlight(flightTarget);
        }
    }
}

sf::Vector2f Airplane::getPosition() const
{
    return sprite.getPosition();
}

void Airplane::startFlight(sf::Vector2f target)
{
    flightTarget = target;
    status = AirplaneStatus::inSky;

    //откалибруем продолжительность полета
    std::string type = role->getType();
    if (type == "WideBody" || type == "Cargo") flightDuration = 50.f;
    else if (type == "NarrowBody") flightDuration = 40.f;
    else if (type == "Regional") flightDuration = 25.f;
    else flightDuration = 15.f;

    flightTimer = 0.f;

    // Центр траектории (сдвиг)
    sf::Vector2f start = sprite.getPosition();
    float offsetX = (std::rand() % 200 - 100); // рандомно влево/вправо
    float offsetY = (std::rand() % 150 - 75);  // вверх/вниз
    flightControlPoint = (start + target) / 2.f + sf::Vector2f(offsetX, offsetY);
}

void Airplane::updateFlight()
{
    if (status != AirplaneStatus::inSky) return;

    flightTimer += 1.f; // тик
    float t = flightTimer / flightDuration;

    if (t >= 1.f)
    {
        // здесь позже будет startLanding()
        status = AirplaneStatus::landing;
        trail.clear();
        return;
    }

    //кривая Безье
    sf::Vector2f P0 = sprite.getPosition();
    sf::Vector2f P1 = flightControlPoint;
    sf::Vector2f P2 = flightTarget;

    sf::Vector2f pos = (1 - t) * (1 - t) * P0 + 2 * (1 - t) * t * P1 + t * t * P2;
    sprite.setPosition(pos);

    // Пунктирная траектория
    if (flightTimer == (int)flightTimer && (int)flightTimer % 3 == 0)
    {
        trail.push_back(pos);
        if (trail.size() > 50) trail.pop_front();
    }
}