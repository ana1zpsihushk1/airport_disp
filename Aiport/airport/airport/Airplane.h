#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "definitions.h"
#include "Role.h"
#include "Strip.h"  
#include "FlightSchedule.h"
#include "Positions.h"

enum class Status
{
    awaitingTakeoff,
    takingOff,
    inAir,
    awaitingLanding,
    landing,
    getCircle,
    landed,
    crashed
};

class Strip;

class Airplane
{
public:
    Airplane(std::string id, std::unique_ptr<Role> role, sf::Time scheduleTime);

    void update(sf::Time deltaTime, sf::Time currentTime);
    void assignStrip(std::shared_ptr<Strip> strip);

    std::string getId() const;
    std::string getRoleType() const;
    Status getStatus() const;
    int getFuel() const;
    float getSpeed() const;
    int getRemainingCircles() const;

    Role* getRole() const { return role.get(); }

    void setStatus(Status status);
    bool hasFuel() const;
    void consumeFuel(int amount);

    sf::Time getScheduleTime() const;
    std::shared_ptr<Strip> getAssignedStrip() const;
    void reduceCircle();

    // Take-off/landing requests
    bool requestLanding(const std::vector<std::shared_ptr<Strip>>& strips, sf::Time currentTime);
    bool requestTakeoff(const std::vector<std::shared_ptr<Strip>>& strips, sf::Time currentTime);

    void crash();
    void land();
    void takeoff();
    void minus(); //penalty

    void setSchedule(const FlightSchedule& schedule);
    FlightSchedule getSchedule() const;

    void draw(sf::RenderWindow& window, sf::Font& font);

    //edem
    void setPath(const std::vector<sf::Vector2f>& newPath);

    void updatePosition(sf::Time deltaTime); // edem po puti

    void setDisplayName(const std::string& name);
    std::string getDisplayName() const;

    sf::CircleShape& getShape() { return shape; }

    bool isVisible() const;
    void setVisible(bool value);

    void setParkingId(int id) { parkingId = id; }
    int getParkingId() const { return parkingId; }

    void setMoving(bool m) { moving = m; }
    bool isMoving() const { return moving; }

    void setArrival(bool value) { isArrival = value; }
    bool getArrival() const { return isArrival; }
private:
    std::string id;
    std::unique_ptr<Role> role;
    Status status;

    int fuel;
    int circlesRemaining;

    sf::Time scheduleTime;
    std::shared_ptr<Strip> stripAssigned;
    int accumulatedMinus = 0;

    sf::Vector2f lastDirection = { 0.f, 0.f };

    FlightSchedule _schedule;

    std::string displayName;

    //draw // potom yberem, esly nado
    std::vector<sf::Vector2f> path;
    std::size_t pathIndex = 0;
    bool moving = false;
    sf::CircleShape shape;

    bool visible = false;

    int parkingId = -1;

    bool isArrival = false;

    // std::vector<sf::Vector2f> route;
    float speed = 10.f;
};