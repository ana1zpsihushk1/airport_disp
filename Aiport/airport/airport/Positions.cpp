#include "Positions.h"

//TAKEOFF
//Cargo & WideBody 
const std::vector<sf::Vector2f> TAKEOFF_BIG_1 = //38 - 34 - 18 - 17
{
    {380.f, 800.f}, {873.f, 800.f}, {1055.f, 800.f}, {1056.f, 160.f}
};

const std::vector<sf::Vector2f> TAKEOFF_BIG_2 = //38 - 39 - 19 - 14
{
    {380.f, 800.f}, {262.f, 800.f}, {262.f, 559.f}, {1370.f, 559.f}
};

//LANDING
//Cargo & WideBody 
const std::vector<sf::Vector2f> LANDING_BIG_1 = //14 - 19 - 39 - 38
{
    {1370.f, 559.f}, {262.f, 559.f}, {262.f, 800.f}, {380.f, 800.f}
};

const std::vector<sf::Vector2f> LANDING_BIG_2 = //17 - 18 - 34
{
    {1056.f, 160.f}, {1055.f, 800.f}, {873.f, 800.f}
};

//TAKEOFF

//NarrowBody & Regional & Local

const std::vector<sf::Vector2f> TAKEOFF_SMALL_1 = //25 - 7
{
   {585.f, 290.f}, {1360.f, 290.f}
};

const std::vector<sf::Vector2f> TAKEOFF_SMALL_2 = //30 - 1
{
    {810.f, 290.f}, {195.f, 290.f}
};
const std::vector<sf::Vector2f> TAKEOFF_SMALL_3 = //2 - 9 - 14
{
    {355.f, 290.f}, {355.f, 559.f}, {1370.f, 559.f}
};

const std::vector<sf::Vector2f> TAKEOFF_SMALL_4 = //30 - 5 - 18 - 33 - 32 - 31 - 16 - 15
{
    {810.f, 290.f}, {1056.f, 290.f}, {1055.f, 800.f}, {1095.f, 840.f}, {1165.f, 853.f}, {1220.f, 828.f}, {1263.f, 750.f}, {1263.f, 145.f}
};

const std::vector<sf::Vector2f> TAKEOFF_SMALL_5 = //30 - 4 - 11 - 8
{
    {810.f, 290.f}, {847.f, 290.f}, {846.f, 559.f}, {200.f, 559.f}
};

//LANDING
//NarrowBody & Regional & Local
const std::vector<sf::Vector2f> LANDING_SMALL_1 = //15 - 16 - 31 - 32 - 33 - 18 - 5 - 30
{
    {1263.f, 145.f}, {1263.f, 750.f}, {1220.f, 828.f}, {1165.f, 853.f}, {1095.f, 840.f}, {1055.f, 800.f}, {1056.f, 290.f}, {810.f, 290.f}
};

const std::vector<sf::Vector2f> LANDING_SMALL_2 = //7 - 25
{
    {1360.f, 290.f}, {585.f, 290.f}
};
const std::vector<sf::Vector2f> LANDING_SMALL_3 = //1 - 25
{
    {195.f, 290.f}, {585.f, 290.f}
};

const std::vector<sf::Vector2f> LANDING_SMALL_4 = //14 - 9 -  2
{
    {1370.f, 559.f}, {355.f, 559.f}, {355.f, 290.f}
};

const std::vector<sf::Vector2f> LANDING_SMALL_5 = //8 - 11 - 4 - 30
{
    {200.f, 559.f}, {846.f, 559.f}, {847.f, 290.f}, {810.f, 290.f}
};
