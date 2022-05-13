#include "explosion.hpp"

#include "../../renderer.hpp"

explosion_t::explosion_t(sf::Vector2f _pos, float _size, sf::Color _color, sf::Uint64 _birth) :
	dynamic_t(_size),
	shape(size),
	TTL(size),
	birth(_birth)
{
	setPosition(_pos);
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(_color);
	shape.setOutlineThickness(2);
	shape.setPosition(getPosition());

	sound.setBuffer(ressources_loader_t::instance().explosion_sound);
	sound.play();
}

void explosion_t::logic(world_t* _world)
{
	sf::Int64 remaining_time = birth + TTL - _world->tick;
	if (remaining_time < 0)
	{
		is_valid = false;
		is_updated = true;
		return;
	}

	shape.setOutlineThickness(remaining_time * size / TTL);

	dynamic_t::logic(_world);
}

void explosion_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(shape, _states);
}

void explosion_t::on_collision(dynamic_t* _other, world_t* _world)
{
}
