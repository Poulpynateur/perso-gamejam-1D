#pragma once

#include "../enemy.hpp"

class enemy_spawner_t : public base_entity_t
{
private:

	float spawn_rate = 80;

public:

	// Hérité via base_entity_t
	virtual void logic(world_t* _world) override;
};

