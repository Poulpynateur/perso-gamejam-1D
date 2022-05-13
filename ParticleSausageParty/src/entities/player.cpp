#include "player.hpp"

#include "../world.hpp"

player_t::player_t(sf::Vector2f _pos) :
	dynamic_t(5, 2, 50),
	ship(nullptr),
	trace(_pos, player_color)
{
	setPosition(_pos);
	setOrigin(size, size);
}

void player_t::logic(world_t* _world)
{
	manage_inputs();
	moveFromRotation();

	trace.setPosition(getPosition());
	trace.logic(_world);
	spawner.setPosition(getPosition());
	spawner.setRotation(getRotation());

	if (ship)
	{
		spawner.logic(_world);
	}

	dynamic_t::logic(_world);

	if (ship)
	{
		ship->update();
	}
}

void player_t::manage_inputs()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotate(-ROTATION_SPEED);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotate(ROTATION_SPEED);
	}
}

void player_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	dynamic_t::draw(_target, _states);

	_target.draw(trace, _states);
	if (ship)
	{
		_target.draw(*ship, _states);
	}
	else
	{

	}
}

void player_t::on_collision(dynamic_t* _other, world_t* _world)
{
	if (typeid(*_other) == typeid(enemy_t))
	{
		if (!ship)
		{
			auto* derived = dynamic_cast<enemy_t*>(_other);
				if (derived)
				{
					ship = new triangle_ship_t(this, derived->ship.type, player_color);
				}
		}
		else
		{
			life -= 1;
			delete ship;
			ship = nullptr;

			_world->list_dynamic.push_back(new explosion_t(getPosition(), 30, sf::Color::Yellow, _world->tick));

			if (life <= 0)
			{
				_world->game_over = true;
			}
		}
	}
	else if (typeid(*_other) == typeid(powerup_t))
	{
		sound.setBuffer(ressources_loader_t::instance().powerup_sound);
		sound.play();

		auto* derived = dynamic_cast<powerup_t*>(_other);
		if (derived->type == enum_powerup_t::BULLET_UP)
		{
			spawner.decrease_spawn_bullet();
		}
		else if (derived->type == enum_powerup_t::MISSILES_UP)
		{
			spawner.decrease_spawn_missile();
		}
		else
		{
			speed += 0.2;
		}
	}
}

void player_t::on_out_bound()
{
	trace.setAllPosition(getPosition());
}
