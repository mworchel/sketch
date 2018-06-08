#pragma once

#include <memory>
#include <vector>

#include "ball.hpp"
#include "force_provider.hpp"

class world {
public:
	world(int width, int height);

	virtual ~world();

	void update(float dt);

	inline int width() const {
		return m_width;
	}

	inline int height() const {
		return m_height;
	}

	void add_ball(const std::shared_ptr<ball>& ball);

	void add_force_provider(const std::shared_ptr<force>& force);

private:
	int                                 m_width;
	int                                 m_height;
	std::vector<std::shared_ptr<ball>>  m_balls;
	std::vector<std::shared_ptr<force>> m_force_providers;
};
