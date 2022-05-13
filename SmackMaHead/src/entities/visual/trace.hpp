#pragma once

#include "../base/entity.hpp"

class trace_t : public render_entity_t
{
private:
	std::vector<sf::Vertex> vertexes;
public:
	trace_t(sf::Vector2f _pos, sf::Color _color, sf::Uint8 _size = 10);

	// Hérité via render_entity_t
	virtual void logic(world_t& _world) override;
	virtual void render(renderer_t& _renderer, world_t& _world) override;
};

