#pragma once

#include <algorithm>

#include <SFML\System.hpp>

#include "ball.hpp"
#include "force_provider.hpp"
#include "vector_helper.hpp"

class gravity_force : public activatable_force {
public:
	inline gravity_force() { }

	inline gravity_force(bool is_active) : activatable_force(is_active) {
	}

	inline sf::Vector2f active_value(const ball& ball) const override {
		return sf::Vector2f(0, 9.81f * ball.mass());
	}
};

class wind_force : public activatable_force {
public:
	inline wind_force() {}

	inline wind_force(bool is_active) : activatable_force(is_active) {}

	inline sf::Vector2f active_value(const ball& ball) const override {
		return sf::Vector2f(5.0f, 0.0f);
	}
};

class friction_force : public activatable_force {
public:
	inline friction_force() {}

	inline friction_force(bool is_active) : activatable_force(is_active) {}

	inline sf::Vector2f active_value(const ball& ball) const override {
		const float c = 10.0f;
		auto friction = ball.velocity();

		// If there is no velocity then there is no friction force
		if (sf::math::magnitude(friction) == 0.0f) {
			return sf::Vector2f();
		}
		
		sf::math::normalize(friction);
		return -friction * c;
	}
};

class point_attractor_force : public activatable_force {
public:
	inline point_attractor_force() {}

	inline point_attractor_force(bool is_active) : activatable_force(is_active) {}

	inline sf::Vector2f& point() {
		return _point;
	}

	inline sf::Vector2f active_value(const ball& ball) const override {
		auto direction = _point - ball.position();
		float mag = sf::math::magnitude(direction);

		if (mag < 5.0f) {
			mag = 5.0f;
		}
		float attraction_value = ((10000 * ball.mass()) / (mag * mag));
		sf::math::normalize(direction);

		if (attraction_value > 50.0f) {
			attraction_value = 50.0f;
		}

		return attraction_value * direction;
	}

private:
	sf::Vector2f _point;
};

