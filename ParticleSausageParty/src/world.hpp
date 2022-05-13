#pragma once
#include <vector>

#include "entities/player.hpp"
#include "entities/enemy.hpp"
#include "entities/spawners/enemy_spawner.hpp"
#include "entities/UI/UI.hpp"

class world_t {
private:

	enemy_spawner_t spawner;

	void clean_all();
public:

	bool game_over = false;
	sf::Uint32 score;

	sf::Uint64 tick;
	sf::Vector2f bounds;

	player_t* player;
	std::vector<dynamic_t*> list_dynamic;
	std::vector<render_entity_t*> list_UI;

	world_t(sf::Vector2f _resolution);
	~world_t();

	void update(sf::Uint64 _tick);
};
