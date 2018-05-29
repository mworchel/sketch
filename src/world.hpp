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
		return _width;
	}

	inline int height() const {
		return _height;
	}

	void add_ball(const std::shared_ptr<ball>& ball);

	void add_force_provider(const std::shared_ptr<force>& force);

private:
	int _width;
	int _height;
	std::vector<std::shared_ptr<ball>> _balls;
	std::vector<std::shared_ptr<force>> _force_providers;
};
