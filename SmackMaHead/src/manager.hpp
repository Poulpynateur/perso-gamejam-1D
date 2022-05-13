#pragma once

#include "world.hpp"

// FIXME : good idea to separate it from the worl, badly executed
class manager_t
{
private:

	void manage_map_finished();
public:
	manager_t(sf::Vector2f _bounds);

	world_t world;

	void update(sf::Uint64 _tick);
	void clean();
};

