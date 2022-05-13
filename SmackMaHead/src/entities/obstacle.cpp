#include "obstacle.hpp"

#include "../world.hpp"
#include "../render/renderer.hpp"

obstacle_t::obstacle_t(sf::Vector2f _position, sf::Vector2f _bounds) :
	position(_position),
	bounds(_bounds)
{
	pixels = new sf::Color[bounds.x * bounds.y]{};

	for (int i = 0; i < bounds.x * bounds.y; i++)
	{
		pixels[i] = sf::Color::Transparent;
	}
}

obstacle_t::~obstacle_t()
{
	delete pixels;
}

void obstacle_t::logic(world_t& _world)
{
	manage_movement(_world);
	position += movement;
}

void obstacle_t::manage_movement(world_t& _world)
{
	if (check_movement(_world, position,			sf::Vector2f(position.x, position.y + bounds.y),	sf::Vector2f(-1, 0))) return;
	if (check_movement(_world, position,			sf::Vector2f(position.x + bounds.x, position.y),	sf::Vector2f(0, -1))) return;
	if (check_movement(_world,  position + bounds,	sf::Vector2f(position.x, position.y + bounds.y),	sf::Vector2f(1, 0))) return;
	if (check_movement(_world, position + bounds,	sf::Vector2f(position.x + bounds.x, position.y),	sf::Vector2f(0, 1))) return;
	// no movement possible go back
	movement = movement * -1.f;
}

bool obstacle_t::check_movement(world_t& _world, sf::Vector2f _pos_1, sf::Vector2f _pos_2, sf::Vector2f _movement)
{
	sf::Vector2f reverse = movement * -1.f;
	if (_world.current_map->is_navigable(_pos_1 + _movement) && _world.current_map->is_navigable(_pos_2 + _movement))
	{
		if (_movement != reverse)
		{
			movement = _movement;
			return true;
		}
	}
	return false;
}

void obstacle_t::render(renderer_t& _renderer, world_t& _world)
{
	for (int x = 0; x < bounds.x; x++)
	{
		for (int y = 0; y < bounds.y; y++)
		{
			_renderer.setVertex(sf::Vertex(position + sf::Vector2f(x, y), pixels[x + y * (int)bounds.x]));
		}
	}
}

bool obstacle_t::is_in_bounds(sf::Vector2f _pos)
{
	return (_pos.x >= position.x && _pos.x <= position.x + bounds.x &&
			_pos.y >= position.y && _pos.y <= position.y + bounds.y);
}

bool obstacle_t::check_collision(sf::Vector2f _point)
{
	if (is_in_bounds(_point))
	{
		on_collision(_point);
		return true;
	}
	return false;
}

// copy past of stain, should find a way to make this more general
void obstacle_t::on_collision(sf::Vector2f _pos)
{
	double max_distance = utils::get_distance_simpl(_pos, sf::Vector2f(_pos.x + radius, _pos.y + radius));
	for (int x = _pos.x - radius; x < _pos.x + radius; x++)
	{
		for (int y = _pos.y - radius; y < _pos.y + radius; y++)
		{
			double distance = utils::get_distance_simpl(_pos, sf::Vector2f(x, y));
			int chance = distance * 100 / max_distance;

			if (rand() % 100 > chance)
			{
				int alpha = 255 - color.a * distance / max_distance + 1;

				sf::Color current = color;
				current.a = alpha;
				if (is_in_bounds(sf::Vector2f(x, y)))
				{
					pixels[x - (int) position.x + (y - (int)position.y) * (int)bounds.x] += current;
				}
			}
		}
	}
}