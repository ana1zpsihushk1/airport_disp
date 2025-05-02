#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "Engine.h"
#include "state.h"
#include "Button.h"

class rulesState : public state
{
public:
	rulesState(GameDataRef data);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Text _rulesText;

	std::unique_ptr<Button> backButton;
};