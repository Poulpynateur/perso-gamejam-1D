#include "map.hpp"

#include "../render/renderer.hpp"
#include <iostream>

map_t::map_t(std::string _map_path)
{
	sf::Image image;
	image.loadFromFile(_map_path);

	bounds = sf::Vector2f(image.getSize().x, image.getSize().y);

	map = new sf::Color[bounds.x * bounds.y];
	const sf::Uint8* pixels = image.getPixelsPtr();
	for (int i = 0; i < image.getSize().x * image.getSize().y; i++ )
	{
		map[i] = sf::Color(
			pixels[i * 4],
			pixels[i * 4 + 1],
			pixels[i * 4 + 2]);

		if (map[i] == respawn_color)
		{
			respawn_pos = sf::Vector2f(i % (int)bounds.y, i / (int)bounds.y);
		}
		else if (map[i] == finish_color)
		{
			finish_pos = sf::Vector2f(i % (int)bounds.y, i / (int)bounds.y);
		}
	}
	create_obstacles();
}

sf::Vector2f map_t::get_obstacle_bounds(sf::Vector2f _pos)
{
	sf::Vector2f obstacle_bounds;
	for (int x_sub = 0; x_sub < bounds.x - _pos.x; x_sub++)
	{
		if (map[(int)_pos.x + x_sub + (int)(_pos.y) * (int)bounds.x] != obstacle_color) break;
		obstacle_bounds.x = x_sub;
	}
	for (int y_sub = 0; y_sub < bounds.y - _pos.y; y_sub++)
	{
		if (map[(int)_pos.x + (int)(_pos.y + y_sub) * (int)bounds.x] != obstacle_color) break;
		obstacle_bounds.y = y_sub;
	}

	for (int x = 0; x < obstacle_bounds.x + 1; x++)
	{
		for (int y = 0; y < obstacle_bounds.y + 1; y++)
		{
			map[(int)_pos.x + x + ((int)_pos.y + y) * (int)bounds.x] = nav_color;
		}
	}

	return obstacle_bounds;
}

void map_t::create_obstacles()
{
	for (int x = 0; x < bounds.x; x++)
	{
		for (int y = 0; y < bounds.y; y++)
		{
			if (map[x + y * (int)bounds.x] == obstacle_color)
			{
				sf::Vector2f obstacle_pos(x, y);
				sf::Vector2f obstacle_bounds = get_obstacle_bounds(obstacle_pos);
				moving_objects.push_back(new obstacle_t(obstacle_pos, obstacle_bounds));
			}
		}
	}
}

map_t::~map_t()
{
	delete map;
	for (auto p : moving_objects)
	{
		delete p;
	}
	moving_objects.clear();
}

bool map_t::check_collision(sf::Vector2f _pos)
{
	if (check_collision_static(_pos)) return true;

	for (obstacle_t* obstacle : moving_objects)
	{
		if (obstacle->check_collision(_pos)) return true;
	}

	return false;
}

bool map_t::check_collision_static(sf::Vector2f _pos)
{
	sf::Color color = color_at(_pos);

	if (color == finish_color)
	{
		map_finished = true;
	}
	else if (color == wall_color) return true;
	return false;
}

bool map_t::is_navigable(sf::Vector2f _pos)
{
	return color_at(_pos) == nav_color;
}

sf::Color map_t::color_at(sf::Vector2f _pos)
{
	return map[(int)((int)(_pos.x) + (int)(_pos.y) * bounds.x)];
}

void map_t::logic(world_t& _world)
{
	for (obstacle_t* obstacle : moving_objects)
	{
		obstacle->logic(_world);
	}
}

void map_t::render(renderer_t& _renderer, world_t& _world)
{
	_renderer.setPixel(respawn_pos, respawn_color);
	_renderer.setPixel(finish_pos, finish_color);

	for (obstacle_t* obstacle : moving_objects)
	{
		obstacle->render(_renderer, _world);
	}
}
