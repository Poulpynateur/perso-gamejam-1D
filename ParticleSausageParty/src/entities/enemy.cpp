#include "enemy.hpp"
#include "../world.hpp"
#include "projectiles/bullet.hpp"

enemy_t::enemy_t(sf::Vector2f _pos) :
	dynamic_t(5, 1, 5),
	ship(this, enum_ship_t::EMPTY, sf::Color::Red)
{
	setPosition(_pos);
	setOrigin(size, size);
}

void enemy_t::logic(world_t* _world)
{
	sf::Vector2f direction = utils::getDirection(getPosition(), _world->player->getPosition());
	rotateToDesired((std::atan2(direction.y, direction.x) * 180 / M_PI));
	float test = getRotation();
	moveFromRotation();

	ship.update();
	dynamic_t::logic(_world);
}

void enemy_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	dynamic_t::draw(_target, _states);

	_target.draw(ship, _states);
}

void enemy_t::on_collision(dynamic_t* _other, world_t* _world)
{
	if (typeid(*_other) == typeid(player_t) || typeid(*_other) == typeid(explosion_t) || typeid(*_other) == typeid(bullet_t) || typeid(*_other) == typeid(missile_t))
	{
		explode(_world);
	}
	else if (typeid(*_other) == typeid(enemy_t))
	{
		// Resolve collision at the closest posible to original position
		sf::Vector2f correction = utils::getDirection(getPosition(), _other->getPosition());
		if (correction.x == 0 && correction.y == 0)
		{
			// Random resolve if exacly the same position
			float random = (float)rand() / (M_PI * 2);
			correction = sf::Vector2f(cos(random), sin(random));
		}
		correction = correction * (float)(utils::getDistance(getPosition(), _other->getPosition()) - (size + _other->size));

		move(correction);
	}
}

void enemy_t::explode(world_t *_world)
{
	is_valid = false;

	_world->score += SCORE_VALUE;

	explosion_t* explosion = new explosion_t(getPosition(), 10, sf::Color::Red, _world->tick);
	explosion->is_collidable = false;
	_world->list_dynamic.push_back(explosion);

	if (rand() % 5 == 0)
	{
		powerup_t *powerup = new powerup_t(getPosition(), enum_powerup_t::BULLET_UP, _world->tick);
		_world->list_dynamic.push_back(powerup);
	}
	else if (rand() % 10 == 0)
	{
		powerup_t* powerup = new powerup_t(getPosition(), enum_powerup_t::MISSILES_UP, _world->tick);
		_world->list_dynamic.push_back(powerup);
	}
	else if (rand() % 5 == 0)
	{
		powerup_t* powerup = new powerup_t(getPosition(), enum_powerup_t::SPEED, _world->tick);
		_world->list_dynamic.push_back(powerup);
	}
}
