#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

//	1 - {195;290}
//	2 - {355;290}
//	3 - {613;290}
//	4 - {847;290}
//	5 - {1056;290}
//	6 - {1263;290}
//	7 - {1360;290}
// 
// 
//	8 - {200;559}
//	9 - {355;559}
//	10 - {613;559}
//	11 - {846;559}
//	12 - {1055;559}
//	13 - {1263;559}
//	14 - {1370;559}
// 
// 
//	15 - {1263;145}
//	16 - {1263;750}
// 
// 
//	17 - {1056;160}
//	18 - {1055;800}
//	
// 
//	19 - {262;559}
// 
//	20 - {320;290}
//	21 - {395;290}
//	22 - {445;290}
//	23 - {490;290}
//	24 - {535;290}
//	25 - {585;290}
//	26 - {630;290}
//	27 - {675;290}
//	28 - {720;290}
//	29 - {770;290}
//	30 - {810;290}
// 
// 
//	31 - {1220;828}
//	32 - {1165;853}
//	33 - {1095;840}
// 
// 
//	34 - {873;800}
//	35 - {750;800}
//	36 - {632;800}
//	37 - {505;800}
//	38 - {380;800}
//	39 - {262;800}
// 
// 
//	40 - {380;559}
//	41 - {505;559}
//	42 - {632;559}
//	43 - {750;559}
//	44 - {873;559}
// 
// 
// 
//	45 - {300;215}
//	46 - {358;215}
//	47 - {410;215}
//	48 - {457;215}
//	49 - {503;215}
//	50 - {550;215}
//	51 - {595;215}
//	52 - {640;215}
//	53 - {687;215}
//	54 - {735;215}
//	55 - {780;215}
// 
// 
// 
//	56 - {380;655}
//	57 - {505;655}
//	58 - {632;655}
//	59 - {750;655}
//	60 - {873;655}
// 
// 
//	61 - {380;717}
//	62 - {505;717}
//	63 - {632;717}
//	64 - {750;717}
//	65 - {873;717}

//  1-4-11-9-2- 20-30 - 45-55

// Example:
/*const std::vector<sf::Vector2f> ROUTE_STRIP_1 = {
    {196.f, 290.f},
    {847.f, 290.f},
    {846.f, 559.f},
    {355.f, 559.f},
    {355.f, 290.f}
};*/

//TAKEOFF
//Cargo & WideBody 
extern const std::vector<sf::Vector2f> TAKEOFF_BIG_1;
extern const std::vector<sf::Vector2f> TAKEOFF_BIG_2;

//LANDING
//Cargo & WideBody 
extern const std::vector<sf::Vector2f> LANDING_BIG_1;
extern const std::vector<sf::Vector2f> LANDING_BIG_2;

//TAKEOFF
//NarrowBody & Regional & Local
extern const std::vector<sf::Vector2f> TAKEOFF_SMALL_1;
extern const std::vector<sf::Vector2f> TAKEOFF_SMALL_2;
extern const std::vector<sf::Vector2f> TAKEOFF_SMALL_3;
extern const std::vector<sf::Vector2f> TAKEOFF_SMALL_4;
extern const std::vector<sf::Vector2f> TAKEOFF_SMALL_5;

//LANDING
//NarrowBody & Regional & Local
extern const std::vector<sf::Vector2f> LANDING_SMALL_1;
extern const std::vector<sf::Vector2f> LANDING_SMALL_2;
extern const std::vector<sf::Vector2f> LANDING_SMALL_3;
extern const std::vector<sf::Vector2f> LANDING_SMALL_4;
extern const std::vector<sf::Vector2f> LANDING_SMALL_5;