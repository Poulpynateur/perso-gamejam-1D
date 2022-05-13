#include "renderer.hpp"

renderer_t::renderer_t(sf::RenderWindow& _window, sf::Vector2f _resolution) :
    resolution(_resolution),
    window(_window),
    clearColor(40, 40, 40, 255)
{
}

void renderer_t::render(world_t &_world)
{
	window.clear(clearColor);

	for (sf::Drawable* element : _world.list_dynamic)
	{
		window.draw(*element);
	}

	for (sf::Drawable* element : _world.list_UI)
	{
		window.draw(*element);
	}

	window.display();
}