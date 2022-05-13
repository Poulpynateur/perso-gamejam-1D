#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>

#include "../base/element.hpp"

class user_interface_t : public render_entity_t
{
private:
	std::vector<sf::CircleShape> lifes;
	sf::Text score;

	sf::Text game_message;

public:

	user_interface_t();

	// Hérité via base_entity_t
	virtual void logic(world_t* _world) override;

	// Hérité via renderable_t
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

