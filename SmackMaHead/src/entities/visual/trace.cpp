#include "trace.hpp"

#include "../../render/renderer.hpp"

trace_t::trace_t(sf::Vector2f _pos, sf::Color _color, sf::Uint8 _size)
{
	position = _pos;
	for (int i = 0; i < _size; i++)
	{
		sf::Color color = _color;
		color.a = 255 - (255 * i / _size);
		vertexes.push_back(sf::Vertex(position, color));
	}
}

void trace_t::logic(world_t& _world)
{
	vertexes[0].position = position;
	// FIXME : ça marche moyen
	for (int i = vertexes.size() - 1; i > 0; i--)
	{
		vertexes[i].position = vertexes[i - 1].position;
	}
}

void trace_t::render(renderer_t& _renderer, world_t& _world)
{
	for (int i = 0; i < vertexes.size(); i++)
	{
		_renderer.setVertex(vertexes[i]);
	}
}
