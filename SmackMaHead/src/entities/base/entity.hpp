#pragma once

#include <SFML/Graphics/Shape.hpp>

class world_t;
class renderer_t;

struct logic_entity_t
{
	bool is_valid = true;
	virtual void logic(world_t& _world) = 0;
};

struct render_entity_t : public logic_entity_t
{
public:
	sf::Vector2f position;

	virtual void render(renderer_t& _renderer, world_t& _world) = 0;
};

struct group_entity_t : public render_entity_t
{
};