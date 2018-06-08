#include "ball.hpp"

#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>

ball::ball(float x, float y, float mass)
	: m_mass(mass), m_position(x, y) {}

ball::~ball() {}

void ball::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	auto circle = sf::CircleShape(radius());
	circle.setOrigin(radius(), radius());
	circle.setPosition(m_position);
  circle.setFillColor(sf::Color(std::min(255.f, radius() * 20.f), std::min(255.f, radius() * 10.f), std::min(255.f, radius() * 5.f)));
	target.draw(circle, states);
}
