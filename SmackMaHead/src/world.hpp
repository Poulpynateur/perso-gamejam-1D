#pragma once

#include "entities/base/entity.hpp"
#include "entities/player.hpp"
#include "events/inputs.hpp"
#include "maps/map.hpp"
#include "UI/UI.hpp"

class world_t
{
private:
	sf::Vector2f bounds;

public:
	int death_count = 0;
	bool game_finish = false;

	int level = 0;

	world_t(sf::Vector2f _bounds);
	~world_t();

	std::vector<map_t*> maps;
	map_t* current_map;

	inputs_t inputs;
	sf::Uint64 tick;

	std::vector<render_entity_t*> list_render;
	player_t* player;
	UI_t UI;
};

