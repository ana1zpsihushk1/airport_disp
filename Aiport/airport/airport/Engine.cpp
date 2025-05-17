#include "Engine.h"
#include "initState.h"
#include "definitions.h"

Engine::Engine(int width, int height, std::string title)
{
	_data->window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);
	
	_data->engine = this;

	if (!_backgroundMusic.openFromFile(MAIN_THEME))
	{
		std::cerr << "[Engine] There is no such track\n";
	}
	else
	{
		_backgroundMusic.setLoop(true);
		_backgroundMusic.setVolume(40.f);
		_backgroundMusic.play();
	}
	
	_data->machine.AddState(StateRef(new initState(this->_data)));

	this->Run();
}

void Engine::Run()
{
	float newTime, frameTime, interpolation;

	float currentTime = this->_clock.getElapsedTime().asSeconds();
	float accumulator = 0.0f;

	while (this->_data->window.isOpen())
	{
		try
		{
			this->_data->machine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= dt)
			{
				_data->machine.GetActiveState()->HandleInput();
				_data->machine.GetActiveState()->Update(dt);
				accumulator -= dt;
			}

			interpolation = accumulator / dt;
			_data->machine.GetActiveState()->Draw(interpolation);
		}
		catch (const std::exception& e)
		{
			std::cerr << "[Engine] Error: " << e.what() << std::endl;
			_data->window.close();
		}
	}
}

void Engine::PlayMainTheme()
{
	if (_backgroundMusic.getStatus() == sf::Music::Playing)
		_backgroundMusic.stop();

	if (_backgroundMusic.openFromFile(MAIN_THEME))
	{
		_backgroundMusic.setLoop(true);
		_backgroundMusic.setVolume(40.f);
		_backgroundMusic.play();
	}
	else
	{
		std::cerr << "[Engine] MAIN_THEME file not found!\n";
	}
}

void Engine::PlayGameTheme()
{
	if (_backgroundMusic.getStatus() == sf::Music::Playing)
		_backgroundMusic.stop();

	if (_backgroundMusic.openFromFile(MAIN_GAME_THEME))
	{
		_backgroundMusic.setLoop(true);
		_backgroundMusic.setVolume(40.f);
		_backgroundMusic.play();
	}
	else
	{
		std::cerr << "[Engine] MAIN_GAME_THEME file not found!\n";
	}
}
