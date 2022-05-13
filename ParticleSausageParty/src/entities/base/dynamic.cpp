#include "dynamic.hpp"
#include "../../world.hpp"

dynamic_t::dynamic_t(sf::Uint16 _size, float _speed, sf::Uint8 _max_rotation):
	size(_size),
	speed(_speed),
	max_rotation(_max_rotation)
{}

void dynamic_t::logic(world_t* _world)
{
	if (is_collidable) check_collision(_world);
	check_out_bound(_world->bounds);
}

void dynamic_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
#ifdef DEBUG

	sf::CircleShape hitbox(size, 40);
	hitbox.setFillColor(sf::Color::Transparent);
	if (is_in_collision) hitbox.setOutlineColor(sf::Color::Magenta);
	else hitbox.setOutlineColor(sf::Color::Green);
	hitbox.setOutlineThickness(1);
	hitbox.setPosition(getPosition());
	hitbox.setOrigin(getOrigin());
	_target.draw(hitbox, _states);

#endif // DEBUG
}

bool dynamic_t::do_collide(dynamic_t* _target)
{
    return
		pow((_target->getPosition().x - getPosition().x), 2) +
		pow((_target->getPosition().y - getPosition().y),2) <=
		pow((_target->size + size),2);
}

void dynamic_t::check_collision(world_t* _world)
{
	is_in_collision = false;
	for (size_t i = 0; i != _world->list_dynamic.size(); ++i)
	{
		dynamic_t* dynamic = _world->list_dynamic[i];

		if (dynamic->is_updated)
		{
			if (dynamic != this && dynamic->is_collidable && dynamic->do_collide(this))
			{
				is_in_collision = true;
				on_collision(dynamic, _world);
				dynamic->on_collision(this, _world);
			}
		}
	}
}

float dynamic_t::rotateToDesired(float _desired_rotation)
{
	float actual = getRotation();
	int angle = _desired_rotation - getRotation();

	if (angle > 180)
	{
		angle = angle - 360;
	}
	else if (angle < -180)
	{
		angle = angle + 360;
	}

	if (std::abs(angle) > max_rotation)
	{
		angle = max_rotation * utils::sgn(angle);
	}

	rotate(angle);
	return angle;
}

void dynamic_t::moveFromRotation()
{
	move(utils::movementFromRotation(getRotation(), speed));
}

void dynamic_t::check_out_bound(sf::Vector2f _bounds)
{
	sf::Vector2f newPos = getPosition();
	bool is_out = false;
	if (getPosition().x < 0)
	{
		newPos.x = _bounds.x;
		is_out = true;
	}
	else if (getPosition().x > _bounds.x)
	{
		newPos.x = 0;
		is_out = true;
	}
	if (getPosition().y < 0)
	{
		newPos.y = _bounds.y;
		is_out = true;
	}
	else if (getPosition().y > _bounds.y)
	{
		newPos.y = 0;
		is_out = true;
	}

	if (is_out)
	{
		setPosition(newPos.x, newPos.y);
		on_out_bound();
	}
}

void dynamic_t::on_out_bound()
{
}