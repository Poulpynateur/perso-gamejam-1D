#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Shape.hpp>

class world_t;
struct renderable_t : public sf::Transformable, public sf::Drawable
{
};

struct base_entity_t
{
	bool is_valid = true;
	bool is_updated = false;
	virtual void logic(world_t* _world) = 0;
};

struct logic_entity_t : public sf::Transformable, public base_entity_t
{
};

struct render_entity_t : public renderable_t, public base_entity_t
{
};