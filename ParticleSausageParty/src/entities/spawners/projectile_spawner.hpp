#pragma once

#include "../base/element.hpp"
#include "../projectiles/bullet.hpp"
#include "../projectiles/missile.hpp"

class projectile_spawner_t : public base_entity_t, public sf::Transformable
{
private:
	sf::Sound sound;

	float spawn_rand = 10;

	int spawn_rate_bullet = 20;
	int spawn_rate_missile = 0;

	bool first_shoot = true;

public:

	// Hérité via base_entity_t
	virtual void logic(world_t* _world) override;

	void decrease_spawn_bullet();
	void decrease_spawn_missile();
};

