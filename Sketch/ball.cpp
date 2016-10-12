#include "ball.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

ball::ball(float x, float y, float mass)
	: _mass(mass), _position(x, y), _angle(0), _angular_velocity(0), _angular_acceleration(0) {}

ball::~ball() {}

void ball::draw(sf::RenderTarget & target, sf::RenderStates states) const {
	float rad = _mass;
	auto circle = sf::CircleShape(rad);
	//auto circle = sf::RectangleShape(sf::Vector2f(rad*2,rad*2));
	circle.setOrigin(rad,rad);
	//circle.setRotation((_angle * 180) / M_PI);
	circle.setPosition(_position);
	target.draw(circle, states);
}
