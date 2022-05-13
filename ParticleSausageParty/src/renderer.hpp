#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <stdlib.h>
#include <time.h>
#include <vector>

#include "world.hpp"

struct base_element_t;

class renderer_t
{
private:

	sf::Vector2f resolution;
	sf::Color clearColor;

public:
	sf::RenderWindow& window;

	renderer_t(sf::RenderWindow& _window, sf::Vector2f _resolution);
	void render(world_t& _world);
};

