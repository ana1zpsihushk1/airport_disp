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
    sprite.setFillColor(sf::Color::Black); //потом цвета менять будем
    sprite.setOrigin(10.f, 10.f); // центр круга
}

void Airplane::tick() //если надо - поправим
{
    updateMovement();

    // если только что завершили взлёт
    /*if (status == AirplaneStatus::inSky && fromNpc && !hasStartedFlight)
    {
        sf::Vector2f flightTarget = (sprite.getPosition().y < 400)
            ? sf::Vector2f(100.f, 600.f)
            : sf::Vector2f(1150.f, 100.f);

        std::cout << "Plane " << id << " start to fly to "
            << flightTarget.x << ", " << flightTarget.y << "\n";
        startFlight(flightTarget);
        hasStartedFlight = true;
    }*/

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
    std::cout << "[TICK] Plane " << id
        << " | Status: " << static_cast<int>(status)
        << " | Pos: (" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")"
        << " | Vel: (" << velocity.x << ", " << velocity.y << ")"
        << " | Speed: " << role->getSpeed()
        << " | Progress: " << takeoffProgress << "/" << takeoffDistance
        << " | FromNpc: " << fromNpc
        << " | HasStartedFlight: " << hasStartedFlight << "\n";
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
    fromNpc = !isPlayer;
    status = AirplaneStatus::takingOff;
    takeoffProgress = 0.f;
    sf::Vector2f start = target->getPosition();
    sf::Vector2f end = isPlayer
        ? start + sf::Vector2f(0.f, currentStrip->getLength())
        : start - sf::Vector2f(0.f, currentStrip->getLength());

    sprite.setPosition(start);
    targetPosition = end;

    sf::Vector2f dir = end - start;
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    velocity = (len > 0) ? dir / len * role->getSpeed() : sf::Vector2f(0.f, 0.f);
    takeoffDistance = len;
    /*std::cout << "[TAKEOFF] " << id
        << " | Speed: " << role->getSpeed()
        << " | Dir: (" << dir.x << ", " << dir.y << ")"
        << " | Vel: (" << velocity.x << ", " << velocity.y << ")"
        << " | Distance: " << takeoffDistance << "\n";*/
    //std::cout << "Takeoff dir = (" << dir.x << ", " << dir.y << "), length = " << takeoffDistance << "\n";
}

/*void Airplane::updateMovement()
{
    std::cout << "updateMovement: id=" << id
        << ", progress=" << takeoffProgress
        << ", distance=" << takeoffDistance
        << ", pos=(" << sprite.getPosition().x << ", " << sprite.getPosition().y << ")\n";

    if (status != AirplaneStatus::takingOff)
        return;

    float step = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    if (takeoffProgress + step >= takeoffDistance)
    {
        sprite.setPosition(targetPosition);
        currentStrip->release();
        velocity = { 0.f, 0.f };
        status = AirplaneStatus::inSky;

        std::cout << "Plane " << id << " end takingoff\n";

        if (fromNpc)
        {
            sf::Vector2f flightTarget = sf::Vector2f(1150.f, 100.f);
            std::cout << "Plane " << id << " start to fly to "
                << flightTarget.x << ", " << flightTarget.y << "\n";
            startFlight(flightTarget);
            hasStartedFlight = true;
        }

        return;
    }

    sprite.move(velocity);
    takeoffProgress += step;
}*/
void Airplane::updateMovement()
{
    if (status != AirplaneStatus::takingOff)
        return;

    float step = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

    if (takeoffProgress + step >= takeoffDistance)
    {
        sprite.setPosition(targetPosition);
        currentStrip->release();
        velocity = { 0.f, 0.f };
        takeoffProgress = takeoffDistance; //
        status = AirplaneStatus::inSky;

        if (fromNpc && !hasStartedFlight)
        {
            sf::Vector2f flightTarget = sf::Vector2f(1150.f, 100.f);
            startFlight(flightTarget);
            hasStartedFlight = true;
        }

        return;
    }

    sprite.move(velocity);
    takeoffProgress += step;
}


sf::Vector2f Airplane::getPosition() const
{
    return sprite.getPosition();
}

void Airplane::startFlight(sf::Vector2f target)
{
   
    flightTarget = target;
    flightStart = sprite.getPosition();
    status = AirplaneStatus::inSky;
    //откалибруем продолжительность полета
    std::string type = role->getType();
    if (type == "WideBody" || type == "Cargo") flightDuration = 50.f;
    else if (type == "NarrowBody") flightDuration = 40.f;
    else if (type == "Regional") flightDuration = 25.f;
    else flightDuration = 15.f;

    flightTimer = 0.f;

    float offsetX = (std::rand() % 200 - 100);
    float offsetY = (std::rand() % 150 - 75);
    flightControlPoint = (flightStart + flightTarget) / 2.f + sf::Vector2f(offsetX, offsetY);
    //std::cout << "Plane " << id << " start to fly to " << target.x << ", " << target.y << "\n";
    std::cout << "[FLIGHT] " << id
        << " | From: (" << flightStart.x << ", " << flightStart.y << ")"
        << " To: (" << flightTarget.x << ", " << flightTarget.y << ")"
        << " | Duration: " << flightDuration << "\n";
}

void Airplane::updateFlight()
{
    if (status != AirplaneStatus::inSky) return;

    flightTimer += 1.f; // тик
    float t = flightTimer / flightDuration;

    if (t >= 1.f)
    {
        sprite.setPosition(flightTarget);
        status = AirplaneStatus::landing;
        trail.clear();
        std::cout << "Plane " << id << " finished flight, switching to landing\n";
        return;
    }

    // Кривая Безье (только одна промежуточная точка)
    sf::Vector2f P0 = flightStart;
    sf::Vector2f P1 = flightControlPoint;
    sf::Vector2f P2 = flightTarget;

    sf::Vector2f pos = (1 - t) * (1 - t) * P0 + 2 * (1 - t) * t * P1 + t * t * P2;
    sprite.setPosition(pos);

    // Пунктирная траектория
    if ((int)flightTimer % 3 == 0)
    {
        trail.push_back(pos);
        if (trail.size() > 50) trail.pop_front();
    }

    std::cout << "Tick flying  " << id << ", time: " << flightTimer << "\n";
}