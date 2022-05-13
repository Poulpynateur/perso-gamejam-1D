#include "UI.hpp"

#include <string>

#include "../../world.hpp"

user_interface_t::user_interface_t()
{
	lifes.push_back(sf::CircleShape(10));
	lifes.push_back(sf::CircleShape(10));
	lifes.push_back(sf::CircleShape(10));

	lifes[0].setFillColor(sf::Color::White);
	lifes[1].setFillColor(sf::Color::White);
	lifes[2].setFillColor(sf::Color::White);
	lifes[0].setOutlineColor(sf::Color::White);
	lifes[1].setOutlineColor(sf::Color::White);
	lifes[2].setOutlineColor(sf::Color::White);
	lifes[0].setOutlineThickness(1);
	lifes[1].setOutlineThickness(1);
	lifes[2].setOutlineThickness(1);

	score.setFont(ressources_loader_t::instance().font);
	score.setFillColor(sf::Color::White);
	score.setPosition(5, 5);
	score.setCharacterSize(20);

	game_message.setFont(ressources_loader_t::instance().font);
	game_message.setFillColor(sf::Color::White);
	game_message.setCharacterSize(50);
}

void user_interface_t::logic(world_t* _world)
{
	score.setString("SCORE : " + std::to_string(_world->score));
	for (int i = 0; i < lifes.size(); i++) {
		if (i + 1 > _world->player->life)
		{
			lifes[i].setFillColor(sf::Color::Transparent);
		}
		lifes[i].setPosition( 5 + i * 25, _world->bounds.y - 25);
	}

	if (_world->game_over)
	{
		game_message.setPosition(_world->bounds.x / 2 - game_message.getLocalBounds().width / 2, _world->bounds.y / 2 - game_message.getLocalBounds().height / 2);
		game_message.setString("GAME OVER");
	}
}

void user_interface_t::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(score, _states);
	_target.draw(game_message, _states);

	for (int i = 0; i < lifes.size(); i++) {
		_target.draw(lifes[i], _states);
	}
}
