#include "player.hpp"

#include "../world.hpp"
#include "../render/renderer.hpp"
#include <iostream>

player_t::player_t(sf::Vector2f _pos) :
	trace_t(_pos, sf::Color::White, 10),
	speed(1),
	movement(0, -speed)
{
}

void player_t::manage_direction()
{
	if (direction < 0) direction = 3;
	if (direction > 3) direction = 0;

	switch (direction)
	{
	case 0: movement = sf::Vector2f(0, -speed); break;
	case 1: movement = sf::Vector2f(speed, 0); break;
	case 2: movement = sf::Vector2f(0, speed); break;
	case 3: movement = sf::Vector2f(-speed, 0); break;
	}
}

void player_t::manage_inputs(const inputs_t& _inputs)
{
	advance = false;
	if (_inputs.left_key)
	{
		direction -= 1;
	}
	if (_inputs.right_key)
	{
		direction += 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		advance = true;
	}

	manage_direction();

	if (advance)
	{
		position += movement;
	}
}

void player_t::logic(world_t& _world)
{
	manage_inputs(_world.inputs);

	manage_collision(_world);
	trace_t::logic(_world);
}

void player_t::manage_collision(world_t& _world)
{
	is_in_collision = _world.current_map->check_collision(position);
	if (is_in_collision)
	{
		_world.list_render.push_back(new stain_t(position, sf::Color::Red, 10));
		position = _world.current_map->respawn_pos;
		_world.death_count += 1;
	}
}

void player_t::render(renderer_t& _renderer, world_t& _world)
{
	if (is_in_collision)
	{
		_renderer.do_flash = true;
	}
	trace_t::render(_renderer, _world);
}
