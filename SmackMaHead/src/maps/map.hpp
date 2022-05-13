#pragma once

#include <string>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>

#include "../entities/base/entity.hpp"

#include "../entities/obstacle.hpp"

class map_t : public render_entity_t
{
private:

	std::vector<obstacle_t* > moving_objects;

	// Statics
	const sf::Color respawn_color = sf::Color(0, 0, 255);
	const sf::Color finish_color = sf::Color(0, 255, 0);

	const sf::Color wall_color = sf::Color(0, 0, 0);
	const sf::Color obstacle_color = sf::Color(40, 40, 40); // 40
	const sf::Color nav_color = sf::Color(200, 200, 200);   // 200

	sf::Vector2f get_obstacle_bounds(sf::Vector2f _pos);
	void create_obstacles();
public:
	map_t(std::string map_path);
	~map_t();

	bool map_finished = false;

	sf::Vector2f respawn_pos;
	sf::Vector2f finish_pos;
	sf::Vector2f bounds;
	sf::Color* map;

	bool check_collision(sf::Vector2f _pos);
	bool check_collision_static(sf::Vector2f _pos);

	bool is_navigable(sf::Vector2f _pos);
	sf::Color color_at(sf::Vector2f _pos);

	// Hérité via render_entity_t
	virtual void logic(world_t& _world) override;
	virtual void render(renderer_t& _renderer, world_t& _world) override;
};

