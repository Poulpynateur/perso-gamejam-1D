#include "UI.hpp"

#include "../world.hpp"
#include "../render/renderer.hpp"

UI_t::UI_t()
{
	font.loadFromFile("ressources/font.ttf");

	player_death.setFont(font);
	player_death.setFillColor(sf::Color::White);
	player_death.setCharacterSize(10);

	main_message.setFont(font);
	main_message.setFillColor(sf::Color::White);
	main_message.setCharacterSize(16);

	smaller_message.setFont(font);
	smaller_message.setFillColor(sf::Color::White);
	smaller_message.setCharacterSize(10);
}

void UI_t::logic(world_t& _world)
{
	player_death.setString(std::to_string(_world.death_count));

	if (_world.game_finish)
	{
		main_message.setPosition(_world.current_map->bounds.x / 2 - main_message.getLocalBounds().width / 2, _world.current_map->bounds.y / 2 - main_message.getLocalBounds().height / 2);
		main_message.setString("GAME FINISHED");
		smaller_message.setPosition(_world.current_map->bounds.x / 2 - smaller_message.getLocalBounds().width / 2, main_message.getPosition().y + main_message.getLocalBounds().height + 5);
		smaller_message.setString("Thanks for playing");
	}
}

void UI_t::render(renderer_t& _renderer, world_t& _world)
{
	_renderer.buffer.draw(player_death);
	if (_world.game_finish)
	{
		_renderer.buffer.draw(main_message);
		_renderer.buffer.draw(smaller_message);
	}
}
