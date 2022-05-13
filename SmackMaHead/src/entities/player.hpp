#pragma once

#include <SFML/Window/Keyboard.hpp>
#include "visual/trace.hpp"
#include "../events/inputs.hpp"
#include "visual/stain.hpp"

class player_t : public trace_t
{
private:

	bool advance;

	float speed;
	sf::Vector2f movement;

	int direction;

	void manage_inputs(const inputs_t& _inputs);
	void manage_direction();
	void manage_collision(world_t& _world);
public:

	bool is_in_collision = false;

	player_t(sf::Vector2f _pos);

	virtual void logic(world_t& _world) override;
	virtual void render(renderer_t& _renderer, world_t& _world) override;
};