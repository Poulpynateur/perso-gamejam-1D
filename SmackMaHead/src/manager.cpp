#include "manager.hpp"

manager_t::manager_t(sf::Vector2f _bounds) :
	world(_bounds)
{
}

void manager_t::update(sf::Uint64 _tick)
{
	world.tick = _tick;

	if (!world.game_finish)
	{
		manage_map_finished();

		world.current_map->logic(world);
		for (size_t i = 0; i != world.list_render.size(); ++i)
		{
			world.list_render[i]->logic(world);
		}
	}
	world.UI.logic(world);
}

void manager_t::manage_map_finished()
{
	if (world.current_map->map_finished)
	{
		if (world.level + 1 >= world.maps.size())
		{
			world.game_finish = true;
		}
		else
		{
			world.current_map = world.maps[world.level + 1];
			world.level += 1;
			world.player->position = world.current_map->respawn_pos;
		}
	}
}

void manager_t::clean()
{
	for (auto it = world.list_render.begin(); it != world.list_render.end();)
	{
		if (!(*it)->is_valid)
		{
			delete (*it);
			(*it) = nullptr;
			it = world.list_render.erase(it);
		}
		else
		{
			++it;
		}
	}
}
