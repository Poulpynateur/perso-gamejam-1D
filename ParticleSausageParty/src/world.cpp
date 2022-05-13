#include "world.hpp"

world_t::world_t(sf::Vector2f _resolution) :
	tick(0),
	bounds(_resolution),
	player(new player_t(sf::Vector2f(bounds.x / 2, bounds.y / 2)))
{
	list_dynamic.push_back(player);
	list_UI.push_back(new user_interface_t());
}

world_t::~world_t()
{
	for (base_entity_t* element : list_dynamic)
	{
		delete element;
	}
}

void world_t::update(sf::Uint64 _tick)
{
	tick = _tick;

	// FIXME : should make a vector of base entity ?
	spawner.logic(this);

	if (!game_over)
	{
		for (size_t i = 0; i != list_dynamic.size(); ++i)
		{
			list_dynamic[i]->logic(this);
			list_dynamic[i]->is_updated = true;
		}
	}

	for (size_t i = 0; i != list_UI.size(); ++i)
	{
		list_UI[i]->logic(this);
		list_UI[i]->is_updated = true;
	}

	clean_all();
}

void world_t::clean_all()
{
	// Cleaning elements
	for (auto it = list_dynamic.begin(); it != list_dynamic.end();)
	{
		(*it)->is_updated = false;
		if (!(*it)->is_valid)
		{
			delete (* it);
			(*it) = nullptr;
			it = list_dynamic.erase(it);
		}
		else
		{
			++it;
		}	
	}
}
