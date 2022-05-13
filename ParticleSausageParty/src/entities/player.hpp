#pragma once
#include <SFML/Graphics/CircleShape.hpp>

#include <SFML/Window/Keyboard.hpp>
#include <iostream>

#include <SFML/Graphics/RenderWindow.hpp>

#include "base/dynamic.hpp"
#include "visual/trace.hpp"
#include "visual/triangle_ship.hpp"

#include "enemy.hpp"
#include "spawners/projectile_spawner.hpp"

class player_t : public dynamic_t
{
private:

	sf::Sound sound;

	const float ROTATION_SPEED = 5;
	const sf::Color player_color = sf::Color::White;
	
	triangle_ship_t *ship;
	trace_t trace;
	projectile_spawner_t spawner;

	void manage_inputs();

public:

	int life = 3;

	player_t(sf::Vector2f _pos);

	// Hérité via base_entity_t
	void logic(world_t *_world) override;
	void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;


	virtual void on_collision(dynamic_t* _other, world_t* _world) override;
	virtual void on_out_bound() override;
};