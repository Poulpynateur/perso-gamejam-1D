#include "world.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <filesystem>

using std::cout; using std::cin;
using std::endl; using std::string;
using std::filesystem::directory_iterator;

world_t::world_t(sf::Vector2f _bounds) :
	tick(0),
	bounds(_bounds)
{
	for (const auto& file : std::filesystem::directory_iterator(std::filesystem::current_path() / "ressources\\maps"))
	{
		maps.push_back(new map_t(file.path().string()));
		
	}
	current_map = maps[0];

	player = new player_t(current_map->respawn_pos);
	list_render.push_back(player);
}

world_t::~world_t()
{
	for (auto map : maps)
	{
		delete map;
	}
}
