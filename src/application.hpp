#pragma once

#include <memory>

#include <SFML\Graphics.hpp>

#include "world.hpp"

class application {
public:
	application();
	~application();

	void run();

private:
	sf::RenderWindow _window;
	std::unique_ptr<world> _world;
};