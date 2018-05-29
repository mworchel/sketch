#include "world.hpp"

#include <algorithm>
#include <iterator>

const float gravity = 0.00981f;// 9.81f;

world::world(int width, int height)
	: _width(width), _height(height) {}

world::~world() {}

void world::update(float dt) {
	// Add forces to each object
	for (const auto& ball : _balls) {
		for (const auto& force_provider : _force_providers) {
			ball->_acceleration += dt*force_provider->value(*ball);
		}
		ball->_acceleration /= ball->mass();
	}


	for (const auto& ball : _balls) {
		if (ball->_position.x < 0){ 
			ball->_position.x = 0;
			ball->_velocity.x = - ball->_velocity.x;
		}
		if (ball->_position.x > _width) {
			ball->_position.x = _width;
			ball->_velocity.x = -ball->_velocity.x;
		}
		if (ball->_position.y > _height) {
			ball->_position.y = _height;
			ball->_velocity.y = -ball->_velocity.y;
		}
		if (ball->_position.y < 0) {
			ball->_position.y = 0;
			ball->_velocity.y = -ball->_velocity.y;
		}
	}

	for (const auto& ball : _balls) {
		ball->update();
		ball->_acceleration = sf::Vector2f();
		ball->_angular_acceleration = 0.0f;
	}
}

void world::add_ball(const std::shared_ptr<ball>& b) {
	_balls.push_back(b);
}

void world::add_force_provider(const std::shared_ptr<force>& force) {
	_force_providers.push_back(force);
}
