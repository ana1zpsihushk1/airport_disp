#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
#include <iostream>

#include "assetManager.h"
#include "inputManager.h"
#include "stateMachine.h"

class Engine;

struct GameData
{
	stateMachine machine;
	sf::RenderWindow window;
	assetManager assets;
	inputManager input;
	Engine* engine = nullptr;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Engine
{
public:
	Engine(int width, int height, std::string title);

	void PlayMainTheme();
	void PlayGameTheme();
private:
	const float dt = 1.0f / 60.0f;
	sf::Clock _clock;
	sf::Music _backgroundMusic;

	GameDataRef _data = std::make_shared<GameData>();
	void Run();
};