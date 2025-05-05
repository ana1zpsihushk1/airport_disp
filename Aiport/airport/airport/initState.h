#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include "Engine.h"
#include "state.h"

class initState : public state
{
public:
	initState(GameDataRef);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

private:
	GameDataRef _data;
	sf::Sprite _background;
	sf::Text _initText;
	sf::Clock _timer;
};