#pragma once

#include <SFML\System.hpp>

class ball;

class force {
public:
	force();

	virtual ~force();

	virtual sf::Vector2f value(const ball& ball) const = 0;
};

class activatable_force : public force {
public:
	inline activatable_force()
		: activatable_force(false) {
	}

	inline activatable_force(bool is_active) : m_is_active(is_active) {
	}

	inline bool& is_active() {
		return m_is_active;
	}

	inline bool is_active() const{
		return m_is_active;
	}

	inline sf::Vector2f value(const ball& ball) const override {
		return m_is_active ? active_value(ball) : sf::Vector2f();
	}

protected:
	virtual sf::Vector2f active_value(const ball& ball) const = 0;

private:
	bool m_is_active;
};