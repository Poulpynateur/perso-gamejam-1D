#include "enemy_spawner.hpp"

#include "../../world.hpp"

void enemy_spawner_t::logic(world_t* _world)
{
	spawn_rate -= _world->tick * 0.0001;

	if (spawn_rate < 1) spawn_rate = 1;

	if (_world->tick % (int) spawn_rate == 0)
	{
		sf::Vector2f random_pos;

		// Make it spawn near borders
		if (rand() & 1)
		{
			random_pos.x = rand() % (int)(_world->bounds.x + 1);
			random_pos.y = (rand() & 1) * _world->bounds.y;
		}
		else
		{
			random_pos.x = (rand() & 1) * _world->bounds.x;
			random_pos.y = rand() % (int)(_world->bounds.y + 1);
		}

		_world->list_dynamic.push_back(new enemy_t(random_pos));
	}
}