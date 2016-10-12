#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class ball : public sf::Drawable {
	friend class world;

public:
	ball(float x, float y, float mass);
	
	virtual ~ball();

	inline void update() {
		_velocity += _acceleration;
		_position += _velocity;

		//_angular_velocity += _angular_acceleration;
		//_angle += _angular_velocity;
	}

	inline sf::Vector2f position() const {
		return _position;
	}

	inline sf::Vector2f velocity() const {
		return _velocity;
	}

	inline float mass() const {
		return _mass;
	}

private:
	float _mass;
	sf::Vector2<float> _position;
	sf::Vector2<float> _velocity;
	sf::Vector2<float> _acceleration;
	float _angle;
	float _angular_velocity;
	float _angular_acceleration;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};