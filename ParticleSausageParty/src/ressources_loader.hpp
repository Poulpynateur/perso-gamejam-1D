#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Audio.hpp>

struct ressources_loader_t
{
private:

	ressources_loader_t()
	{
		straight_grid.loadFromFile("ressources/straight_grid.png");
		simple_grid.loadFromFile("ressources/simple_grid.png");
		double_grid.loadFromFile("ressources/double_grid.png");

		explosion_sound.loadFromFile("ressources/explosion.wav");
		shoot_sound.loadFromFile("ressources/shoot.wav");
		powerup_sound.loadFromFile("ressources/powerup.wav");
		missile_sound.loadFromFile("ressources/rocket.wav");

		font.loadFromFile("ressources/bahnschrift.ttf");
	}

public:
	static ressources_loader_t& instance()
	{
		static ressources_loader_t INSTANCE;
		return INSTANCE;
	}

	sf::Texture straight_grid;
	sf::Texture simple_grid;
	sf::Texture double_grid;

	sf::SoundBuffer explosion_sound;
	sf::SoundBuffer shoot_sound;
	sf::SoundBuffer powerup_sound;
	sf::SoundBuffer missile_sound;

	sf::Font font;
};

