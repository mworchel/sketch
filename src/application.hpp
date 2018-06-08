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
	sf::RenderWindow m_window;
	world            m_world;
};