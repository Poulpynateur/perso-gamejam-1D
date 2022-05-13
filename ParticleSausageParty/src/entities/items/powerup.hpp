#pragma once

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "../base/dynamic.hpp"
#include "../../ressources_loader.hpp"

enum enum_powerup_t
{
	BULLET_UP,
	MISSILES_UP,
	SPEED
};

class powerup_t : public dynamic_t
{
private:
	sf::Uint64 birth;
	sf::Uint32 TTL = 500;

public:
	sf::Text text;
	enum_powerup_t type;

	powerup_t(sf::Vector2f _pos, enum_powerup_t _type, sf::Uint64 _birth);

	virtual void logic(world_t* _world) override;
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	// Hérité via dynamic_t
	virtual void on_collision(dynamic_t* _other, world_t* _world) override;

};

