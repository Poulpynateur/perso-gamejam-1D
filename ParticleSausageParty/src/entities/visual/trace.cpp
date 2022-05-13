#include "trace.hpp"

#include "../../world.hpp"

trace_t::trace_t(sf::Vector2f _pos, sf::Color _color, bool _fade, sf::Uint8 _size, sf::Uint16 _delay) :
	line(sf::LineStrip, _size),
	size(_size),
	delay(_delay)
{
	setPosition(_pos);
	for (int i = 0; i < size; i++)
	{
		line[i].position = getPosition();
		if (_fade)
		{
			line[i].color = sf::Color(_color.r * i / size, _color.g * i / size, _color.b * i / size, _color.a * i / size);
		}
		else
		{
			line[i].color = _color;
		}
	}
}

void trace_t::logic(world_t *_world)
{
	if (_world->tick % delay == 0)
	{
		for (int i = 0; i < (size - 1); i++) {
			line[i].position = line[i + 1].position;
		}
	}

	line[size - 1].position = getPosition();
}

void trace_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(line, _states);
}

void trace_t::setAllPosition(sf::Vector2f _pos)
{
	setPosition(_pos);
	for (int i = 0; i < size; i++)
	{
		line[i].position = _pos;
	}
}
