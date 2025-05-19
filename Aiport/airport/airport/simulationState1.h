#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "state.h"

#include "AirportPlayer.h"
//#include "Airplane.h"
//#include "RoleFabric.h"

/*class simulationState1 : public state
{
public:
	simulationState1(GameDataRef data);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

private:
	GameDataRef _data;

	std::shared_ptr<AirportPlayer> AirPlayer;
	std::shared_ptr<AirportNpc> AirNpc;
	std::vector<std::shared_ptr<Airplane>> activePlanes;
	int planeId = 0;
};*/

class simulationState1 : public state
{
public:
	simulationState1(GameDataRef data);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

private:
	GameDataRef _data;

	std::shared_ptr<AirportPlayer> AirPlayer;

	sf::Sprite backgroundSprite;
};