#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../world.hpp"
#include "../entities/base/entity.hpp"

// TODO : create a renderer_interface_t for entities
class renderer_t
{
private:
	bool is_effect_updated = false;
	sf::Vector2f bounds;

	sf::VertexArray points;
	sf::Color clear_color;

	
	sf::Sprite buffer_sprite;

	sf::Uint8* effects_pixels;
	sf::Texture effects_texture;
	sf::Sprite effects_sprite;

	void handle_map_finished(world_t& _world);
public:

	bool do_flash = false;

	sf::RenderTexture buffer;
	sf::RenderWindow& window;
	renderer_t(sf::RenderWindow& _window, sf::Vector2f _bounds);

	void render(world_t& _world);

	// renderer_interface_t
	void setVertex(const sf::Vertex& _vertex);
	void setPixel(sf::Vector2f _pos, sf::Color _color);
};

