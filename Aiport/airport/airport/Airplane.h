#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <memory>

#include "Role.h"
#include "Strip.h"  

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

    void setStatus(Status status);
    bool hasFuel() const;
    void consumeFuel(int amount);

    sf::Time getScheduleTime() const;
    std::shared_ptr<Strip> getAssignedStrip() const;
    void reduceCircle();

    // Запросы взлет/посадка
    bool requestLanding(const std::vector<std::shared_ptr<Strip>>& strips, sf::Time currentTime);
    bool requestTakeoff(const std::vector<std::shared_ptr<Strip>>& strips, sf::Time currentTime);

    void crash();
    void land();
    void takeoff();
    void minus(); //штраф

private:
    std::string id;
    std::unique_ptr<Role> role;
    Status status;

    int fuel;
    int circlesRemaining;

    sf::Time scheduleTime;
    std::shared_ptr<Strip> stripAssigned;
    int accumulatedMinus = 0;
};