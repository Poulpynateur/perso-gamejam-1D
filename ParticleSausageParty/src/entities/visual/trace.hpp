#pragma once
#include <SFML/Graphics/VertexArray.hpp>

#include "../base/element.hpp"

class trace_t : public base_entity_t, public renderable_t
{
private:
	sf::Uint16 delay;
	sf::VertexArray line;
	sf::Uint8 size;

public:
	trace_t(sf::Vector2f _pos, sf::Color _color, bool _fade = true, sf::Uint8 _size = 10, sf::Uint16 _delay = 4);

	// Hérité via base_entity_t
	void logic(world_t *_world) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	void setAllPosition(sf::Vector2f _pos);
};

