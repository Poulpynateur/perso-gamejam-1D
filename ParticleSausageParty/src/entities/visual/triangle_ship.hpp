#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include "../../ressources_loader.hpp"
#include "../base/dynamic.hpp"

enum enum_ship_t
{
	EMPTY,
	SIMPLE_STRIP,
	DOUBLE_STRIP,
	FULL
};

class triangle_ship_t : public sf::CircleShape
{
private:
	dynamic_t* parent;

public:
	enum_ship_t type;

	triangle_ship_t(dynamic_t* _parent, enum_ship_t _type, sf::Color _color);
	void update();
};

