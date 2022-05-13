#include "powerup.hpp"

#include "../../renderer.hpp"

powerup_t::powerup_t(sf::Vector2f _pos, enum_powerup_t _type, sf::Uint64 _birth) :
	dynamic_t(5),
	type(_type),
	birth(_birth)
{
	setPosition(_pos);

	text.setFont(ressources_loader_t::instance().font);
	text.setFillColor(sf::Color::White);

	text.setPosition(_pos.x, _pos.y - 5);
	text.setCharacterSize(15);

	if (type == enum_powerup_t::BULLET_UP)
	{
		text.setString("B");
	}
	else if (type == enum_powerup_t::MISSILES_UP)
	{
		text.setString("M");
	}
	else
	{
		text.setString("S");
	}
}

void powerup_t::logic(world_t* _world)
{
	if (birth + TTL < _world->tick)
	{
		is_valid = false;
	}

	text.setFillColor(sf::Color(255,255,255, 255 - (_world->tick - birth) * 255 / TTL));

	dynamic_t::logic(_world);
}

void powerup_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(text, _states);
	dynamic_t::draw(_target, _states);
}

void powerup_t::on_collision(dynamic_t* _other, world_t* _world)
{
	if (typeid(*_other) == typeid(player_t))
	{
		is_valid = false;
	}
}
