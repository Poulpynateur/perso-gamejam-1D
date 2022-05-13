#pragma once

#include <SFML/System/Vector2.hpp>
#include <cmath>

namespace utils
{
	inline double get_distance(sf::Vector2f _a, sf::Vector2f _b) {
		return std::sqrt(std::pow(_b.x - _a.x, 2) + std::pow(_b.y - _a.y, 2));
	}

	inline double get_distance_simpl(sf::Vector2f _a, sf::Vector2f _b) {
		return std::abs(_b.x - _a.x) + std::abs(_b.y - _a.y);
	}
}