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

    void update(sf::Time deltaTime);
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

    void draw(sf::RenderWindow& window);

    //edem
    void setPath(const std::vector<sf::Vector2f>& newPath);

    //void updatePosition(float dt); // edem po puti

    void setDisplayName(const std::string& name);
    std::string getDisplayName() const;

private:
    std::string id;
    std::unique_ptr<Role> role;
    Status status;

    int fuel;
    int circlesRemaining;

    sf::Time scheduleTime;
    std::shared_ptr<Strip> stripAssigned;
    int accumulatedMinus = 0;

    FlightSchedule _schedule;

    std::string displayName;

    //draw // potom yberem, esly nado
    std::vector<sf::Vector2f> path;
    std::size_t pathIndex = 0;
    bool moving = false;
    sf::CircleShape shape;

};