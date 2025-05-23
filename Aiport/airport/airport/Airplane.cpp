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
    if (!visible && currentTime >= scheduleTime)
        setVisible(true);

    //if (status == Status::landed)
    //    return;

    if (moving)
        updatePosition(deltaTime);

    if (visible && (status == Status::inAir || status == Status::getCircle))
    {
        consumeFuel(static_cast<int>(deltaTime.asSeconds()));
        if (!hasFuel())
            status = Status::crashed;
    }

    if (!moving && (status == Status::landing || status == Status::takingOff))
    {
        status = (status == Status::landing ? Status::landed : Status::inAir);

        if (status == Status::landed)
            lastDirection = { 0.f, 0.f };
    }

    if (getStatus() == Status::landing && reachedFinalDestination()) {
        setStatus(Status::parking);
    }

    else if (getStatus() == Status::parking && reachedFinalDestination()) {
        setMoving(false);
        setStatus(Status::stayingPark);
    }
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
        if (true)
        {
            if (strip->canAccept(*role) && strip->isAvailableAt(currentTime))
            {
                assignStrip(strip);
                strip->reserveUntil(currentTime + sf::seconds(10));

                std::vector<sf::Vector2f> takeoffPath = strip->getTakeoffPath(); // предполагается, что он у тебя есть
                setPath(takeoffPath);
                moving = true;
                visible = true;
                status = Status::takingOff;

                if (takeoffPath.size() >= 2)
                {
                    sf::Vector2f dir = takeoffPath.back() - takeoffPath[takeoffPath.size() - 2];
                    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
                    if (len != 0)
                        dir /= len;

                    sf::Vector2f offscreenTarget = takeoffPath.back() + dir * 1000.f;
                    path.push_back(offscreenTarget);
                }

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
            minus();
            setStatus(Status::awaitingTakeoff);
            return false;
        }
    }

    return false;
}

void Airplane::land()
{
    setStatus(Status::landing);
    if (stripAssigned)
    {
        auto landingPath = stripAssigned->getLandingPath();
        if (isArrival && !parkingRoute.empty())
            landingPath.insert(landingPath.end(), parkingRoute.begin(), parkingRoute.end());
        setPath(landingPath);
    }
}

void Airplane::takeoff()
{
    setStatus(Status::takingOff);

    if (stripAssigned)
    {
        auto takeoffPath = stripAssigned->getTakeoffPath();

        if (!parkingRoute.empty())
        {
            std::vector<sf::Vector2f> reverseParking = parkingRoute;
            std::reverse(reverseParking.begin(), reverseParking.end());

            reverseParking.insert(reverseParking.end(), takeoffPath.begin(), takeoffPath.end());
            setPath(reverseParking);
        }
        else
            setPath(takeoffPath);
    }
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

    // Загрузим шрифт из определения (один раз)
    static sf::Font labelFont;
    static bool isLoaded = false;
    if (!isLoaded) {
        if (!labelFont.loadFromFile(FONT_FOR_PLANES)) {
            std::cerr << "Ошибка: не удалось загрузить шрифт: " << FONT_FOR_PLANES << std::endl;
            return;
        }
        isLoaded = true;
    }

    // Создаем подпись
    sf::Text label;
    label.setFont(labelFont);
    label.setString(displayName.empty() ? "NO_NAME" : displayName);
    label.setCharacterSize(18);
    label.setFillColor(sf::Color::White);
    //label.setStyle(sf::Text::Bold);

    // Центрируем и позиционируем
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    label.setPosition(shape.getPosition().x, shape.getPosition().y - shape.getRadius() - 20.f);

    // Добавим фон
    sf::RectangleShape bg(sf::Vector2f(textBounds.width + 10.f, textBounds.height + 10.f));
    bg.setFillColor(sf::Color(0, 0, 0, 150));
    bg.setOrigin(bg.getSize().x / 2.f, bg.getSize().y / 2.f);
    bg.setPosition(label.getPosition());

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

void Airplane::setParkingRoute(const std::vector<sf::Vector2f>& route)
{
    parkingRoute = route;
}

const std::vector<sf::Vector2f>& Airplane::getParkingRoute() const
{
    return parkingRoute;
}

//pod voprosom
void Airplane::updatePosition(sf::Time deltaTime)
{
    if (path.empty()) {
        if (!isArrival && lastDirection != sf::Vector2f(0.f, 0.f)) {
            sf::Vector2f currentPos = shape.getPosition();
            sf::Vector2f offscreenTarget = currentPos + lastDirection * 1000.f;
            path.push_back(offscreenTarget);
        }
        else {
            moving = false;
            return;
        }
    }

    sf::Vector2f currentPos = shape.getPosition();
    sf::Vector2f targetPos = path.front();
    sf::Vector2f direction = targetPos - currentPos;

    float dist = std::hypot(direction.x, direction.y);
    float step = speed * deltaTime.asSeconds();

    if (dist < step) {
        shape.setPosition(targetPos);
        path.erase(path.begin());

        if (!path.empty()) {
            // Пересчитаем новое направление
            sf::Vector2f nextDir = path.front() - shape.getPosition();
            float len = std::hypot(nextDir.x, nextDir.y);
            if (len > 0)
                lastDirection = nextDir / len;
        }

    }
    else {
        direction /= dist;
        lastDirection = direction;  // <- критично: сохраняем направление
        shape.move(direction * step);
    }

    moving = true;
}