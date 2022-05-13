#pragma once

#include "../../utils.hpp"
#include "../base/dynamic.hpp"
#include "../visual/trace.hpp"

class bullet_t : public dynamic_t
{
private:
	trace_t trace;

	sf::Vector2f movement;
	// Time To Die
	sf::Uint32 TTD;

public:
	bullet_t(sf::Vector2f _pos, float _rotation, float _speed, sf::Uint32 _TTD);

	// Hérité via base_entity_t
	void logic(world_t* _world) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	// Hérité via collapsible_t
	virtual void on_collision(dynamic_t* _other, world_t* _world) override;
	virtual void on_out_bound() override;
};

