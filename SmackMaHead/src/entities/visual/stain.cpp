#include "stain.hpp"

#include "../../render/renderer.hpp"

stain_t::stain_t(sf::Vector2f _pos, sf::Color _color, sf::Uint8 _radius) :
	radius(_radius),
	color(_color),
	position(_pos)
{
}

void stain_t::logic(world_t& _world)
{
	// Cupcacke time
	is_valid = false;
}

void stain_t::render(renderer_t& _renderer, world_t& _world)
{
	double max_distance = utils::get_distance_simpl(position, sf::Vector2f(position.x + radius, position.y + radius));
	for (int x = position.x - radius; x < position.x + radius; x++)
	{
		for (int y = position.y - radius; y < position.y + radius; y++)
		{
			double distance = utils::get_distance_simpl(position, sf::Vector2f(x, y));
			int chance = distance * 100 / max_distance;

			if (rand() % 100 > chance)
			{
				int alpha = 255 - color.a * distance / max_distance + 1;

				sf::Color current = color;
				if (!_world.current_map->check_collision_static(sf::Vector2f(x, y)))
				{
					current = floor_color;
				}

				_renderer.setPixel(sf::Vector2f(x, y), sf::Color(current.r, current.g, current.b, 255 - color.a * distance / max_distance));
			}
		}
	}
}
