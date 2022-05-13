#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>

#include "base/entity.hpp"

class obstacle_t : public render_entity_t
{
private:
	// Should be using stain
	sf::Color color = sf::Color::Red;
	sf::Uint8 radius = 10;

	sf::Vector2f position;
	sf::Vector2f bounds;

	sf::Color* pixels;

	sf::Vector2f movement;

	void manage_movement(world_t& _world);
	bool check_movement(world_t& _world, sf::Vector2f _pos_1, sf::Vector2f _pos_2, sf::Vector2f _movement);
	void on_collision(sf::Vector2f _pos);
	bool is_in_bounds(sf::Vector2f _pos);
public:

	obstacle_t(sf::Vector2f _position, sf::Vector2f _bounds);
	~obstacle_t();

	virtual void logic(world_t& _world) override;
	virtual void render(renderer_t& _renderer, world_t& _world) override;

	bool check_collision(sf::Vector2f _point);
};

