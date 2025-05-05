#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Airport.h"
#include "Strip.h"

class AirportPlayer : public Airport
{
public:
	bool hasFreeSlot() const { return airplanes.size() < capacity; }
	void setLevel(int level);
	int getCurLoad() const { return airplanes.size(); }
	const std::vector<std::shared_ptr<Airplane>>& getAirplanes() const { return airplanes; }
	void deleteAirplane(const std::string& id);

	void tick() override;
	void acceptAirplane(std::shared_ptr<Airplane> plane) override;

	AirportPlayer(sf::Vector2f position, sf::Vector2f size);
	void draw(sf::RenderWindow& window);

	void initStrip();
	void processTakeoff();
	Strip* findSuitableStrip(const std::string& typeName);
private:
	std::vector<std::shared_ptr<Airplane>> airplanes;
	int curLevel = 0;
	int capacity = 5;
	std::vector<Strip> strips;

	sf::RectangleShape shape;
};