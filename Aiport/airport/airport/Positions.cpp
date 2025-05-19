#include "Positions.h"

//  TAKEOFF
// 
//  Cargo & WideBody 
//  38 - 34 - 18 - 17
const std::vector<sf::Vector2f> TAKEOFF_BIG_1 = 
{
    {380.f, 800.f},
    {873.f, 800.f},
    {1055.f, 800.f},
    {1056.f, 160.f}
};

//38 - 39 - 19 - 14
const std::vector<sf::Vector2f> TAKEOFF_BIG_2 = 
{
    {380.f, 800.f},
    {262.f, 800.f},
    {262.f, 559.f}, 
    {1370.f, 559.f}
};

//  LANDING
// 
//  Cargo & WideBody 
//  14 - 19 - 39 - 38
const std::vector<sf::Vector2f> LANDING_BIG_1 = 
{
    {1370.f, 559.f}, 
    {262.f, 559.f}, 
    {262.f, 800.f}, 
    {380.f, 800.f}
};

//  17 - 18 - 34
const std::vector<sf::Vector2f> LANDING_BIG_2 =
{
    {1056.f, 160.f}, 
    {1055.f, 800.f},
    {873.f, 800.f}
};

//  TAKEOFF

//  NarrowBody & Regional & Local
//  25 - 7
const std::vector<sf::Vector2f> TAKEOFF_SMALL_1 = 
{
   {585.f, 290.f}, 
   {1360.f, 290.f}
};

//  30 - 1
const std::vector<sf::Vector2f> TAKEOFF_SMALL_2 = 
{
    {810.f, 290.f},
    {195.f, 290.f}
};

//  2 - 9 - 14
const std::vector<sf::Vector2f> TAKEOFF_SMALL_3 = 
{
    {355.f, 290.f}, 
    {355.f, 559.f},
    {1370.f, 559.f}
};

//  30 - 5 - 18 - 33 - 32 - 31 - 16 - 15
const std::vector<sf::Vector2f> TAKEOFF_SMALL_4 =
{
    {810.f, 290.f},
    {1056.f, 290.f},
    {1055.f, 800.f}, 
    {1095.f, 840.f}, 
    {1165.f, 853.f},
    {1220.f, 828.f},
    {1263.f, 750.f},
    {1263.f, 145.f}
};

//  30 - 4 - 11 - 8
const std::vector<sf::Vector2f> TAKEOFF_SMALL_5 = 
{
    {810.f, 290.f},
    {847.f, 290.f}, 
    {846.f, 559.f},
    {200.f, 559.f}
};

//  LANDING
//  NarrowBody & Regional & Local
//  15 - 16 - 31 - 32 - 33 - 18 - 5 - 30
const std::vector<sf::Vector2f> LANDING_SMALL_1 = 
{
    {1263.f, 145.f}, {1263.f, 750.f}, {1220.f, 828.f}, {1165.f, 853.f}, {1095.f, 840.f}, {1055.f, 800.f}, {1056.f, 290.f}, {810.f, 290.f}
};

//  7 - 25
const std::vector<sf::Vector2f> LANDING_SMALL_2 = 
{
    {1360.f, 290.f}, {585.f, 290.f}
};

//  1 - 25
const std::vector<sf::Vector2f> LANDING_SMALL_3 = 
{
    {195.f, 290.f}, 
    {585.f, 290.f}
};

//  14 - 9 -  2
const std::vector<sf::Vector2f> LANDING_SMALL_4 = 
{
    {1370.f, 559.f}, 
    {355.f, 559.f}, 
    {355.f, 290.f}
};

//  8 - 11 - 4 - 30
const std::vector<sf::Vector2f> LANDING_SMALL_5 = 
{
    {200.f, 559.f}, 
    {846.f, 559.f}, 
    {847.f, 290.f}, 
    {810.f, 290.f}
};