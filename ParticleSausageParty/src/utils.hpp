#pragma once

#include <SFML/System/Vector2.hpp>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>

namespace utils
{
	template <typename T>
	inline int sgn(T val) {
		return (T(0) < val) - (val < T(0));
	}

	inline sf::Vector2f normalize(sf::Vector2f _vector)
	{
		float bigger = std::max(std::abs(_vector.x), std::abs(_vector.y));

		if (bigger == 0) return _vector;
		return _vector / bigger;
	}

	inline sf::Vector2f getDirection(sf::Vector2f _from, sf::Vector2f _to)
	{
		return normalize(sf::Vector2f(_to - _from));
	}

	inline float getDistance(sf::Vector2f _from, sf::Vector2f _to)
	{
		return sqrt( pow(_from.x - _to.x, 2) + pow(_from.y - _to.y, 2));
	}

	inline sf::Vector2f movementFromRotation(float _rotation, float _speed)
	{
		return sf::Vector2f(cos(_rotation * M_PI / 180) * _speed, sin(_rotation * M_PI / 180) * _speed);
	}
}