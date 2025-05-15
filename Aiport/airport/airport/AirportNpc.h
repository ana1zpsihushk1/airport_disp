#pragma once
#include <iostream>
#include <queue>

#include "Airport.h"
#include "Strip.h"

class AirportNpc : public Airport
{
public:
	void tick(float dt) override;
	void deleteAirplane(const std::string& id);
	void acceptAirplane(std::shared_ptr<Airplane> plane) override;
	Strip* findSuitableStrip(const std::string& typeName) override;
	AirportNpc(sf::Vector2f position, sf::Vector2f size);
	void draw(sf::RenderWindow& window);
	void initStrip();

	void setPlayerAirport(Airport* airport);
	void processTakeoff();
	
private:
	std::vector<std::shared_ptr<Airplane>> airplanes;

	sf::RectangleShape shape;

	std::vector<Strip> strips;
	Airport* playerAirport = nullptr;
};