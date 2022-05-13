#pragma once
#include <math.h>


#include "../../utils.hpp"
#include "element.hpp"

// TODO : cut in moving_entity and collision_entity
struct dynamic_t : public base_entity_t, public renderable_t
{
protected:
	bool is_in_collision = false;

	float speed;
	sf::Uint8 max_rotation;

protected:
	virtual bool do_collide(dynamic_t* _target);
	virtual void check_collision(world_t* _world);

public:

	bool is_collidable = true;
	sf::Uint16 size;

	dynamic_t(sf::Uint16 _size, float _speed = 0, sf::Uint8 _max_rotation = 0);

	float rotateToDesired(float _desired_rotation);
	void moveFromRotation();

	// Hérité via base_element_t
	virtual void logic(world_t* _world) override;
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	virtual void on_collision(dynamic_t* _other, world_t* _world) = 0;

	virtual void on_out_bound();
	virtual void check_out_bound(sf::Vector2f _bounds);
};

