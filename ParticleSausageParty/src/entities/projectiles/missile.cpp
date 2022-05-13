#include "missile.hpp"

#include "../../renderer.hpp"

missile_t::missile_t(sf::Vector2f _pos, float _rotation, float _speed, sf::Uint32 _TTD) :
	dynamic_t(2),
	circle(size),
	trace(_pos, sf::Color(250, 200, 200), true, 4, 20),
	TTD(_TTD),
	max_speed(_speed)
{
	setPosition(_pos);
	setRotation(_rotation);
	circle.setFillColor(sf::Color::White);
}

void missile_t::logic(world_t* _world)
{
	if (_world->tick > TTD)
	{
		is_valid = false;
		is_updated = true;
		explode(_world);
		return;
	}

	if (speed < max_speed) speed += speed_tick;

	rotate(rand() % (int)(rotate_rand) - rotate_rand / 2);

	moveFromRotation();

	circle.setPosition(getPosition());
	trace.setPosition(getPosition());
	trace.logic(_world);

	dynamic_t::logic(_world);
}

void missile_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(trace, _states);
	_target.draw(circle, _states);
}

void missile_t::on_collision(dynamic_t* _other, world_t* _world)
{
	if (typeid(*_other) == typeid(enemy_t))
	{
		is_valid = false;
		explode(_world);
	}
}

void missile_t::on_out_bound()
{
	trace.setAllPosition(getPosition());
}

void missile_t::explode(world_t* _world)
{
	_world->list_dynamic.push_back(new explosion_t(getPosition(), 15, sf::Color::Yellow, _world->tick));
}
