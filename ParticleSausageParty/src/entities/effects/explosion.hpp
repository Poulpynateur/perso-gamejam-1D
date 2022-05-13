#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include "../base/dynamic.hpp"

#include <SFML/Audio/Sound.hpp>

class explosion_t : public dynamic_t
{
private:
	sf::Sound sound;

	sf::Uint64 birth;
	sf::CircleShape shape;
	float TTL;

public:
	explosion_t(sf::Vector2f _pos, float size, sf::Color _color, sf::Uint64 _birth);

	// Hérité via base_entity_t
	void logic(world_t* _world) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	// Hérité via collapsible_t
	virtual void on_collision(dynamic_t* _other, world_t* _world) override;
};