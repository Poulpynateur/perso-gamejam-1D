#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <typeinfo>

#include "../../utils.hpp"
#include "../base/dynamic.hpp"
#include "../visual/trace.hpp"
#include "../effects/explosion.hpp"

class missile_t : public dynamic_t
{
private:
	sf::CircleShape circle;

	float rotate_rand = 10;
	float speed_tick = 0.1;
	float max_speed;
	trace_t trace;

	// Time To Die
	sf::Uint32 TTD;

public:
	missile_t(sf::Vector2f _pos, float _rotation, float _speed, sf::Uint32 _TTD);

	// Hérité via base_entity_t
	void logic(world_t* _world) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	// Hérité via collapsible_t
	virtual void on_collision(dynamic_t* _other, world_t* _world) override;
	virtual void on_out_bound() override;

	void explode(world_t* _world);
};

