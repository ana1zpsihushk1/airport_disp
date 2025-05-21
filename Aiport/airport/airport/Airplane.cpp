#include <random>
#include <sstream>
#include <cmath>

#include "Airplane.h"
#include "AirplaneUtils.h"
#include "GameClock.h"
#include "definitions.h"

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


Airplane::Airplane(std::string id, std::unique_ptr<Role> role, sf::Time scheduleTime)
    : id(std::move(id)),
    role(std::move(role)),
    status(Status::awaitingTakeoff),
    fuel(this->role->getInitFuel()),
    circlesRemaining(this->role->getMaxCircles()),
    scheduleTime(scheduleTime) {/*âîçìîæíî òóò áóäåò îòðèñîâêà*/
}

void Airplane::update(sf::Time deltaTime, sf::Time currentTime)
{
    if (!visible && currentTime >= scheduleTime) {
        setVisible(true);
    }

    if (visible && moving)
        updatePosition(deltaTime);

    if (visible && (status == Status::inAir || status == Status::getCircle))
    {
        consumeFuel(static_cast<int>(deltaTime.asSeconds()));
        if (!hasFuel())
        {
            status = Status::crashed;
        }
    }

    if (!moving && (status == Status::landing || status == Status::takingOff))
        status = (status == Status::landing ? Status::landed : Status::inAir);
}

bool Airplane::requestLanding(const std::vector<std::shared_ptr<Strip>>& strips, sf::Time currentTime)
{
    for (auto& strip : strips)
    {
        // ÇÄÅÑÜ ÄÎËÆÅÍ ÁÛÒÜ ÎÒÂÅÒ ÄÈÑÏÅÒ×ÅÐÀ
        if (1) //äèñïåò÷åð ðàçðåøèë ñåñòü... ÄÎÏÈÑÀÒÜ
        {
            //ïðîâåðÿåì íà ñîâìåñòèìîñòü
            if (strip->canAccept(*role) && strip->isAvailableAt(currentTime))
            {
                assignStrip(strip);
                strip->reserveUntil(currentTime + sf::seconds(10));
                //ïîñàäêà (sfml êîîðäèíàòû)
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
        else //îòïàðâèëè íà âòîðîé êðóã
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
        // ÇÄÅÑÜ ÄÎËÆÅÍ ÁÛÒÜ ÎÒÂÅÒ ÄÈÑÏÅÒ×ÅÐÀ
        if (1) //äèñïåò÷åð ðàçðåøèë ñåñòü... ÄÎÏÈÑÀÒÜ
        {
            //ïðîâåðÿåì íà ñîâìåñòèìîñòü
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
            // Çàäåðæêà
            minus();
            setStatus(Status::awaitingTakeoff);
            return false;
        }
    }
}

void Airplane::land()
{
    setStatus(Status::landing);
    if (stripAssigned)
        setPath(stripAssigned->getLandingPath());
}

void Airplane::takeoff()
{
    setStatus(Status::takingOff);
    if (stripAssigned)
        setPath(stripAssigned->getTakeoffPath());
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

sf::Time Airplane::getScheduleTime() const
{
    return sf::Time();
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
    //ÂÛÇÎÂ ÊÎÍÖÀ ÈÃÐÛ???
}

//SCHEDULE MOMENT
/*sf::Time Airplane::getScheduleTime() const
{
    return scheduleTime;
}*/ // hz teper nado ili net

void Airplane::setSchedule(const FlightSchedule& schedule)
{
    _schedule = schedule;
}

FlightSchedule Airplane::getSchedule() const
{
    return _schedule;
}

void Airplane::draw(sf::RenderWindow& window, sf::Font& font)
{
    if (!visible) return;

    window.draw(shape);

    sf::Text label;
    label.setFont(font);
    label.setString(displayName);
    label.setCharacterSize(14);
    label.setFillColor(MAIN_WHITE_COLOR);
    label.setPosition(shape.getPosition().x - 25.f, shape.getPosition().y - 35.f);

    sf::RectangleShape bg(sf::Vector2f(label.getLocalBounds().width + 8.f, 20.f));
    bg.setFillColor(sf::Color(0, 0, 0, 100));
    bg.setPosition(label.getPosition().x - 4.f, label.getPosition().y - 2.f);

    window.draw(bg);
    window.draw(label);
}

//edem

//vozmojno nado peredelat
void Airplane::setPath(const std::vector<sf::Vector2f>& newPath)
{
    path = newPath;
    pathIndex = 0;
    moving = !path.empty();
    if (moving)
    {
        shape.setPosition(path[0]);
    }
}

void Airplane::setDisplayName(const std::string& name)
{
    displayName = name;
}

std::string Airplane::getDisplayName() const
{
    return displayName;
}

bool Airplane::isVisible() const
{
    return visible;
}

void Airplane::setVisible(bool value)
{
    visible = value;
}

//pod voprosom
void Airplane::updatePosition(sf::Time deltaTime)
{
    if (pathIndex >= path.size())
    {
        moving = false;
        return;
    }

    sf::Vector2f currentPos = shape.getPosition();
    sf::Vector2f target = path[pathIndex];
    sf::Vector2f direction = target - currentPos;

    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance < 5.f)
    {
        pathIndex++;
        if (pathIndex >= path.size())
        {
            moving = false;
            status = (status == Status::takingOff ? Status::inAir : Status::landed);
        }
        return;
    }

    sf::Vector2f unit = direction / distance;
    float speed = role->getSpeed() * 25.f;
    shape.move(unit * speed * deltaTime.asSeconds());

    float angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;
    shape.setRotation(angle);
}