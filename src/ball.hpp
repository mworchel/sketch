#pragma once

#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>

class ball : public sf::Drawable {
	friend class world;

public:
	ball(float x, float y, float mass);
	
	virtual ~ball();

	inline void update() {
		m_velocity += m_acceleration;
		m_position += m_velocity;
    m_acceleration = { 0.f, 0.f };
	}

  inline float mass() const
  {
    return m_mass;
  }

	inline sf::Vector2f position() const {
		return m_position;
	}

  inline sf::Vector2f& position()
  {
    return m_position;
  }

	inline sf::Vector2f velocity() const {
		return m_velocity;
	}

  inline sf::Vector2f& velocity()
  {
    return m_velocity;
  }

  inline sf::Vector2f& acceleration()
  {
    return m_acceleration;
  }

  inline float radius() const
  {
    return m_mass;
  }

private:
	float        m_mass;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;

	// Inherited via Drawable
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};