#include "Airplane.h"

Airplane::Airplane(std::string id, std::unique_ptr<Role> role, sf::Time scheduleTime)
    : id(std::move(id)),
    role(std::move(role)),
    status(Status::awaitingTakeoff),
    fuel(this->role->getInitFuel()),
    circlesRemaining(this->role->getMaxCircles()),
    scheduleTime(scheduleTime) {}

void Airplane::update(sf::Time deltaTime) 
{
    if (status == Status::inAir || status == Status::getCircle) 
    {
        consumeFuel(static_cast<int>(deltaTime.asSeconds()));
        if (!hasFuel()) 
        {
            status = Status::crashed;
            //GAME OVER
        }
    }
}

bool Airplane::requestLanding(const std::vector<std::shared_ptr<Strip>>& strips, sf::Time currentTime) 
{
    for (auto& strip : strips) 
    {
        // ЗДЕСЬ ДОЛЖЕН БЫТЬ ОТВЕТ ДИСПЕТЧЕРА
        if (1) //диспетчер разрешил сесть... ДОПИСАТЬ
        {
            //проверяем на совместимость
            if (strip->canAccept(*role) && strip->isAvailableAt(currentTime))
            {
                assignStrip(strip);
                strip->reserveUntil(currentTime + sf::seconds(10));
                //посадка (sfml координаты)
                land();
                return true;
            }
            else
            {
                status = Status::crashed;
                crash();
                return true;
            }
        }
        else //отпарвили на второй круг
        {
            minus();
            setStatus(Status::getCircle);
            return false;
        }
    }
}

bool Airplane::requestTakeoff(const std::vector<std::shared_ptr<Strip>>& strips, sf::Time currentTime) 
{
    for (auto& strip : strips) 
    {
        // ЗДЕСЬ ДОЛЖЕН БЫТЬ ОТВЕТ ДИСПЕТЧЕРА
        if (1) //диспетчер разрешил сесть... ДОПИСАТЬ
        {
            //проверяем на совместимость
            if (strip->canAccept(*role) && strip->isAvailableAt(currentTime))
            {
                assignStrip(strip);
                strip->reserveUntil(currentTime + sf::seconds(10));
                takeoff();
                return true;
            }
            else
            {
                status = Status::crashed;
                crash();
                return true;
            }
        }
        else
        {
            // Задержка
            minus();
            setStatus(Status::awaitingTakeoff);
            return false;
        }
    }
}

void Airplane::land() 
{
    setStatus(Status::landing);
    //реализация посадки 
}

void Airplane::takeoff() 
{
    setStatus(Status::takingOff);
    //реализация взлета
}

void Airplane::minus() 
{
    accumulatedMinus += role->getInitMinus();
}


void Airplane::assignStrip(std::shared_ptr<Strip> strip) 
{
    stripAssigned = strip;
}

void Airplane::setStatus(Status newStatus)
{
    status = newStatus;
}

std::string Airplane::getId() const 
{
    return id;
}

std::string Airplane::getRoleType() const 
{
    return role->getType();
}

Status Airplane::getStatus() const 
{
    return status;
}

int Airplane::getFuel() const 
{
    return fuel;
}

std::shared_ptr<Strip> Airplane::getAssignedStrip() const
{
    return stripAssigned;
}

float Airplane::getSpeed() const
{
    return role->getSpeed();
}

int Airplane::getRemainingCircles() const
{
    return circlesRemaining;
}

void Airplane::reduceCircle()
{
    if (circlesRemaining > 0)
    {
        --circlesRemaining;
    }
}

bool Airplane::hasFuel() const 
{
    return fuel > 0;
}

void Airplane::consumeFuel(int amount) 
{
    fuel -= amount;
    if (fuel < 0) fuel = 0;
}

void Airplane::crash()
{
    //ВЫЗОВ КОНЦА ИГРЫ???
    
}

//SCHEDULE MOMENT
sf::Time Airplane::getScheduleTime() const 
{
    return scheduleTime;
}
