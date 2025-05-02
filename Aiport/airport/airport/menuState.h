#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Engine.h"
#include "state.h"
#include "Button.h"

class menuState : public state
{
public:
	menuState(GameDataRef);

	void Init() override;
	void HandleInput() override;
	void Update(float dt) override;
	void Draw(float dt) override;

private:
	GameDataRef _data;

	sf::Sprite _background;
	sf::Font _font;

	std::unique_ptr<Button> _newGameButton;
	std::unique_ptr<Button> _continueButton;
	std::unique_ptr<Button> _rulesButton;
};
