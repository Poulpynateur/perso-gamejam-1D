#include "triangle_ship.hpp"


triangle_ship_t::triangle_ship_t(dynamic_t* _parent, enum_ship_t _type, sf::Color _color) :
	parent(_parent),
	type(_type),
	sf::CircleShape(_parent->size, 3)
{
	setOutlineThickness(1);
	setOutlineColor(_color);

	if (type != enum_ship_t::EMPTY)
	{
		setFillColor(_color);
	}
	else
	{
		setFillColor(sf::Color::Transparent);
	}

	switch (type)
	{
	case SIMPLE_STRIP:
		setTexture(&ressources_loader_t::instance().simple_grid);
		break;
	case DOUBLE_STRIP:
		setTexture(&ressources_loader_t::instance().double_grid);
		break;
	}
}

void triangle_ship_t::update()
{
	setOrigin(parent->getOrigin());
	setPosition(parent->getPosition());
	setRotation(parent->getRotation() + 90);
}
