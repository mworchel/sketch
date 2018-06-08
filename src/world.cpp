#include "world.hpp"

#include <algorithm>
#include <iterator>

const float gravity = 0.00981f;// 9.81f;

world::world(int width, int height)
	: m_width(width), m_height(height) {}

world::~world() {}

void world::update(float dt) {
	// Add forces to all the balls
	for (auto& ball : m_balls) {
		for (const auto& force_provider : m_force_providers) {
			ball->acceleration() += dt * force_provider->value(*ball);
		}
		ball->acceleration() /= ball->mass();
	}

  // Enforce balls to stay in our small constraint rectangular world
	for (auto& ball : m_balls) {
    auto& position = ball->position();
    auto& velocity = ball->velocity();
    float const radius = ball->radius();

		if (position.x - radius < 0){
			position.x = radius;
			velocity.x = - velocity.x;
		}
		if (position.x + radius > m_width) {
			position.x = m_width - radius;
			velocity.x = -velocity.x;
		}
		if (position.y + radius > m_height) {
			position.y = m_height - radius;
			velocity.y = - velocity.y;
		}
		if (position.y - radius < 0) {
			position.y = radius;
			velocity.y = -velocity.y;
		}
	}

	for (auto& ball : m_balls) {
		ball->update();
	}
}

void world::add_ball(const std::shared_ptr<ball>& b) {
	m_balls.push_back(b);
}

void world::add_force_provider(const std::shared_ptr<force>& force) {
	m_force_providers.push_back(force);
}
