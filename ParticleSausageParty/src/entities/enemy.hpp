#pragma once
#include <SFML/Graphics/CircleShape.hpp>
#include <math.h>

#include "../utils.hpp"
#include "base/dynamic.hpp"
#include "visual/triangle_ship.hpp"
#include "items/powerup.hpp"

class enemy_t : public dynamic_t
{
private:

	const int SCORE_VALUE = 100;

public:
	triangle_ship_t ship;
	enemy_t(sf::Vector2f _pos);

	// Hérité via base_entity_t
	virtual void logic(world_t* _world) override;
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	// Hérité via collapsible_t
	virtual void on_collision(dynamic_t* _other, world_t* _world) override;

	void explode(world_t* _world);
};