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
//  15 - 16 - 31 - 32 - 33 - 18 - 5 - 3
const std::vector<sf::Vector2f> LANDING_SMALL_1 = 
{
    {1263.f, 145.f}, 
    {1263.f, 750.f}, 
    {1220.f, 828.f}, 
    {1165.f, 853.f}, 
    {1095.f, 840.f}, 
    {1055.f, 800.f}, 
    {1056.f, 290.f}, 
    {613.f, 290.f}
};

//  7 - 3
const std::vector<sf::Vector2f> LANDING_SMALL_2 = 
{
    {1360.f, 290.f}, 
    {613.f, 290.f}
};

//  1 - 4 - 3
const std::vector<sf::Vector2f> LANDING_SMALL_3 = 
{
    {195.f, 290.f}, 
    {847.f, 290.f},
    {613.f, 290.f}
};

//  14 - 10 -  3
const std::vector<sf::Vector2f> LANDING_SMALL_4 = 
{
    {1370.f, 559.f}, 
    {613.f, 559.f}, 
    {613.f, 290.f}
};

//  8 - 11 - 4 - 3
const std::vector<sf::Vector2f> LANDING_SMALL_5 = 
{
    {200.f, 559.f}, 
    {846.f, 559.f}, 
    {847.f, 290.f}, 
    {613.f, 290.f}
};

/*

//  PARKING SMALL

//  3 - 20 - 45
const std::vector<sf::Vector2f> PARKING_SMALL_1 =
{
    {613.f, 290.f},
    {320.f, 290.f},
    {300.f, 215.f}

};

//  3 - 21 - 46
const std::vector<sf::Vector2f> PARKING_SMALL_2 =
{
    {613.f, 290.f},  
    {395.f, 290.f},
    {358.f, 215.f}
};

//  3 - 22 - 47
const std::vector<sf::Vector2f> PARKING_SMALL_3 =
{
    {613.f, 290.f}, 
    {445.f, 290.f}, 
    {410.f, 215.f}
};

//  3 - 23 - 48
const std::vector<sf::Vector2f> PARKING_SMALL_4 =
{
    {613.f, 290.f}, 
    {490.f, 290.f}, 
    {457.f, 215.f}
};

//  3 - 24 - 49
const std::vector<sf::Vector2f> PARKING_SMALL_5 =
{
    {613.f, 290.f}, 
    {535.f, 290.f}, 
    {503.f, 215.f},
};

//  3 - 25 - 50
const std::vector<sf::Vector2f> PARKING_SMALL_6 =
{
    {613.f, 290.f},
    {585.f, 290.f},
    {550.f, 215.f}
};

//  3 - 26 - 51
const std::vector<sf::Vector2f> PARKING_SMALL_7 =
{
    {613.f, 290.f},
    {630.f, 290.f}, 
    {595.f, 215.f}
};

//  3 - 27 - 52
const std::vector<sf::Vector2f> PARKING_SMALL_8 =
{
    {613.f, 290.f}, 
    {675.f, 290.f},
    {640.f, 215.f}
};

//  3 - 28 - 53
const std::vector<sf::Vector2f> PARKING_SMALL_9 =
{
    {613.f, 290.f},
    {720.f, 290.f},
    {687.f, 215.f}
};

//  3 - 29 - 54
const std::vector<sf::Vector2f> PARKING_SMALL_10 =
{
    {613.f, 290.f}, 
    {770.f, 290.f},
    {735.f, 215.f}
};

//  3 - 30 - 55
const std::vector<sf::Vector2f> PARKING_SMALL_11 =
{
    {613.f, 290.f},
    {810.f, 290.f},
    {780.f, 215.f}
};


//Big airplanes

//  39 - 38 - 56
const std::vector<sf::Vector2f> PARKING_BIG_1 =
{
    {262.f, 800.f}, 
    {380.f, 800.f},
    {380.f, 655.f}
};

//  39 - 37 - 57
const std::vector<sf::Vector2f> PARKING_BIG_2 =
{
    {262.f, 800.f},
    {505.f, 800.f},
    {505.f, 655.f}
};

//  39 - 36 - 58
const std::vector<sf::Vector2f> PARKING_BIG_3 =
{
    {262.f, 800.f},
    {632.f, 800.f},
    {632.f, 655.f}
};

//  39 - 35 - 59
const std::vector<sf::Vector2f> PARKING_BIG_4 =
{
    {262.f, 800.f},
    {750.f, 800.f},
    {750.f, 655.f}
};

//  39 - 34 - 60
const std::vector<sf::Vector2f> PARKING_BIG_5 =
{
    {262.f, 800.f},
    {873.f, 800.f}, 
    {873.f, 655.f}
};

//  39 - 38 - 61
const std::vector<sf::Vector2f> PARKING_BIG_6 =
{
    {262.f, 800.f},
    {380.f, 800.f},
    {380.f, 717.f}
};

//  39 - 37 - 62
const std::vector<sf::Vector2f> PARKING_BIG_7 =
{
    {262.f, 800.f}, 
    {505.f, 800.f}, 
    {505.f, 717.f}
};

//  39 - 36 - 63
const std::vector<sf::Vector2f> PARKING_BIG_8 =
{
    {262.f, 800.f}, 
    {632.f, 800.f}, 
    {632.f, 717.f}
};

//  39 - 35 - 64
const std::vector<sf::Vector2f> PARKING_BIG_9 =
{
    {262.f, 800.f},
    {750.f, 800.f}, 
    {750.f, 717.f}
};

//  39 - 34 - 65
const std::vector<sf::Vector2f> PARKING_BIG_10 =
{
    {262.f, 800.f}, 
    {873.f, 800.f},
    {873.f, 717.f}
};

*/