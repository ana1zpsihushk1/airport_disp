#pragma once
#include <SFML/Graphics.hpp>
#include "Engine.h"
#include "state.h"

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

	sf::Sprite _background;
	sf::Text _label;
};