#include "renderer.hpp"

renderer_t::renderer_t(sf::RenderWindow& _window, sf::Vector2f _bounds) :
	window(_window),
	bounds(_bounds),
	clear_color(40, 40, 40, 255),
	points(sf::Points, 1000)
{
	sf::View view(bounds / 2.f, bounds);
	window.setView(view);

	buffer.create(bounds.x, bounds.y);
	buffer_sprite = sf::Sprite(buffer.getTexture());

	// For effects
	effects_pixels = new sf::Uint8[bounds.x * bounds.y * 4];
	std::fill_n(effects_pixels, bounds.x * bounds.y * 4, 0);

	effects_texture.create(bounds.x, bounds.y);
	effects_sprite = sf::Sprite(effects_texture);
}

void renderer_t::render(world_t& _world)
{
	handle_map_finished(_world);

	if (do_flash)
	{
		window.clear(sf::Color::White);
		do_flash = false;
	}
	else
	{
		window.clear(clear_color);
		points.clear();
		buffer.clear(sf::Color::Transparent);

		_world.current_map->render(*this, _world);
		for (size_t i = 0; i != _world.list_render.size(); ++i)
		{
			_world.list_render[i]->render(*this, _world);
		}
		_world.UI.render(*this, _world);

		if (is_effect_updated)
		{
			effects_texture.update(effects_pixels);
			is_effect_updated = false;
		}

		buffer.draw(points);
		buffer.display();

		window.draw(effects_sprite);
		window.draw(buffer_sprite);
	}

	window.display();
}

void renderer_t::handle_map_finished(world_t& _world)
{
	if (_world.current_map->map_finished)
	{
		is_effect_updated = true;
		for (int i = 0; i < bounds.x * bounds.y * 4; i++)
		{
			effects_pixels[i] = 0;
		}
	}
}

void renderer_t::setVertex(const sf::Vertex& _vertex)
{
	points.append(_vertex);
}

void renderer_t::setPixel(sf::Vector2f _pos, sf::Color _color)
{
	sf::Uint64 index = _pos.x * 4 + _pos.y * bounds.x * 4;

	sf::Uint16 alpha = effects_pixels[index + 3] + _color.a;
	if (alpha > 255) alpha = 255;

	effects_pixels[index] = _color.r;
	effects_pixels[index + 1] = _color.g;
	effects_pixels[index + 2] = _color.b;
	effects_pixels[index + 3] = alpha;

	is_effect_updated = true;
}