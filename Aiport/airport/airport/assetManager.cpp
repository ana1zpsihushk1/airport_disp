#include <SFML/Graphics.hpp>
#include "assetManager.h"

void assetManager::LoadTexture(const std::string& name, const std::string& fileName)
{
	if (_textures.find(name) != _textures.end())
		return;

	sf::Texture tex;
	if (tex.loadFromFile(fileName))
		_textures[name] = tex;
}

sf::Texture& assetManager::GetTexture(const std::string& name)
{
	if (_textures.count(name) == 0)
	{
		static sf::Texture emptyTexture;
		return emptyTexture;
	}
	return _textures[name];
}

void assetManager::LoadFont(const std::string& name, const std::string& fileName)
{
	if (_fonts.find(name) != _fonts.end())
		return;

	sf::Font font;
	if (font.loadFromFile(fileName))
		_fonts[name] = font;
}

sf::Font& assetManager::GetFont(const std::string& name)
{
	if (_fonts.count(name) == 0)
	{
		static sf::Font emptyFont;
		return emptyFont;
	}
	return _fonts[name];
}
