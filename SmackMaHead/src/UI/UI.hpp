#pragma once

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../entities/base/entity.hpp"

class UI_t : public render_entity_t
{
private:
	sf::Font font;

	sf::Text player_death;

	sf::Text main_message;
	sf::Text smaller_message;

public:
	UI_t();

	virtual void logic(world_t& _world) override;
	virtual void render(renderer_t& _renderer, world_t& _world) override;
};

