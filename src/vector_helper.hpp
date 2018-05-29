#pragma once

#include <math.h>

#include <SFML\System.hpp>

namespace sf {
	namespace math {
		template<typename T>
		inline static T magnitude(const sf::Vector2<T>& vector) {
			return static_cast<T>(sqrt(static_cast<double>((vector.x * vector.x) + (vector.y * vector.y))));
		}

		template<typename T>
		inline static void normalize(sf::Vector2<T>& vector) {
			auto mag = magnitude(vector);
			vector.x /= mag;
			vector.y /= mag;
		}
	}
}
