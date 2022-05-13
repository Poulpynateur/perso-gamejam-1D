#pragma once

#include "../base/entity.hpp"
#include "../../utils.hpp"

class stain_t : public render_entity_t
{
private:
	sf::Color floor_color = sf::Color(50,50,50);

	sf::Color color;
	sf::Vector2f position;
	sf::Uint8 radius;

public:
	stain_t(sf::Vector2f _pos, sf::Color _color, sf::Uint8 _radius = 5);

	// Hérité via render_entity_t
	virtual void logic(world_t& _world) override;
	virtual void render(renderer_t& _renderer, world_t& _world) override;
};