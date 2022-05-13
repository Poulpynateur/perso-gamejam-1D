#include "bullet.hpp"

#include "../../renderer.hpp"

bullet_t::bullet_t(sf::Vector2f _pos, float _rotation, float _speed, sf::Uint32 _TTD) :
	dynamic_t(2),
	trace(_pos, sf::Color::White, true, 4),
	TTD(_TTD)
{
	setPosition(_pos);
	movement = utils::movementFromRotation(_rotation, _speed);
}

void bullet_t::logic(world_t* _world)
{
	if (_world->tick > TTD)
	{
		is_valid = false;
		is_updated = true;
		return;
	}
	move(movement);

	trace.setPosition(getPosition());
	trace.logic(_world);

	dynamic_t::logic(_world);
}

void bullet_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(trace, _states);
}

void bullet_t::on_collision(dynamic_t* _other, world_t* _world)
{
	if (typeid(*_other) != typeid(player_t))
	{
		is_valid = false;
	}
}

void bullet_t::on_out_bound()
{
	trace.setAllPosition(getPosition());
}
