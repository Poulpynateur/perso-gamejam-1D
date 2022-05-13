#include "projectile_spawner.hpp"

#include "../../world.hpp"

void projectile_spawner_t::logic(world_t* _world)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (first_shoot || (_world->tick % spawn_rate_bullet == 0))
		{
			float rotation = getRotation() + rand() % (int)(spawn_rand)-spawn_rand / 2;
			_world->list_dynamic.push_back(new bullet_t(getPosition(), rotation, 10, _world->tick + 100));

			sound.setBuffer(ressources_loader_t::instance().shoot_sound);
			sound.play();
		}

		if ((spawn_rate_missile != 0  && first_shoot) || (spawn_rate_missile != 0 && _world->tick % spawn_rate_missile == 0))
		{
			_world->list_dynamic.push_back(new missile_t(getPosition(), getRotation(), 10, _world->tick + 100));

			sound.setBuffer(ressources_loader_t::instance().missile_sound);
			sound.play();
		}
		first_shoot = false;
	}
	else
	{
		first_shoot = true;
	}
}

void projectile_spawner_t::decrease_spawn_bullet()
{
	if (spawn_rate_bullet == 0) spawn_rate_bullet = 20;
	spawn_rate_bullet -= 2;

	if (spawn_rate_bullet <= 0) spawn_rate_bullet = 1;
}

void projectile_spawner_t::decrease_spawn_missile()
{
	if (spawn_rate_missile == 0) spawn_rate_missile = 30;
	spawn_rate_missile -= 2;

	if (spawn_rate_missile <= 0) spawn_rate_missile = 1;
}
